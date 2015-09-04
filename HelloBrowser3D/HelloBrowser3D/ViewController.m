//
//  ViewController.m
//
//  Hello3DBrowser
//
//  Copyright (c) 2015 Aumentia. All rights reserved.
//
//  Written by Pablo GM <info@aumentia.com>, January 2015
//

#import "ViewController.h"
#import "CaptureSessionManager.h"

#define kAccelerometerFrequency        90.0     //Hz

@interface ViewController ()
{
    // Browser instance
    _DBrowser                   *my3dBrowser;
    
    // Gestures
    UIPanGestureRecognizer      *_panRecognizer;
    UIPinchGestureRecognizer    *_pinchRecognizer;
    UIRotationGestureRecognizer *_rotationRecognizer;
    
    // Camera
    CaptureSessionManager       *_captureManager;
    UIView                      *_cameraView;
    
    // Radar Plugin
    PoiRadarController          *_radarController;
    NSMutableArray              *_poisArray;
    
    // Motion
    CMMotionManager             *motionManager;
    
    Poi                         *currentSelectedPOI;
    
    BOOL                        isIphone;
    
    CLLocation                  *lastLocation;
}

@end

@implementation ViewController

@synthesize locationManager;


#pragma mark - View Life Cycle

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
	// Do any additional setup after loading the view, typically from a nib.
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
        isIphone = YES;
    else
        isIphone = NO;
    
    // Add camera
    [self initCapture];
    
    // Initiliaze
    my3dBrowser = [[_DBrowser alloc] initBrowser:CGRectMake(0, 0, self.view.bounds.size.width, self.view.bounds.size.height) withKey:@"627a859b970b7d2cbb337e99ada9610f13ae1b64" setDebug:YES representation:geographical];
    
    // Delegate
    [my3dBrowser setDelegate:self];
    
    // Transparent brackground
    [my3dBrowser setBackgroundColor:[UIColor clearColor]];
    
    // Add view
    [self.view addSubview:my3dBrowser];
    [self.view bringSubviewToFront:my3dBrowser];
    
    // Add gestures
    [self addGestureEvents];
    
    // Init location manager
    [self setupLocationManager];
    
    // Set connection properties
    //[my3dBrowser setUrlConnections:ASYNC displayLoading:YES];
    
    // Init motion
    [self initMotionManager];
    [my3dBrowser setMotionManager:motionManager];
    
    // Radar
    _poisArray = [[NSMutableArray alloc] init];
    [self setupRadar];
    
    self.view.backgroundColor = [UIColor clearColor];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    // Remove POIs
    [my3dBrowser removeAllPois];
    
    // Remove camera
    [self removeCapture];
    
    // Remove gestures
    [self removeGestures];
    
    // Remove motion manager
    [self removeMotionManager];
    
    // Remove location manager
    [self removeLocationManager];
    
    // Remove radar
    [self removeRadar];
    
    // Remove notifications
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    // Release memory
    [my3dBrowser releaseBrowser];
    [my3dBrowser removeFromSuperview];
    [self releaseMemory];
    
    for (UIView *view in [self.view subviews])
    {
        [view removeFromSuperview];
    }
    
    [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];

    [[NSNotificationCenter defaultCenter] removeObserver:self];
}


#pragma mark - Add POIs

- (BOOL)addPOIs:(CLLocation*)location
{
    // SAMPLE COORDS
    float _lat = location.coordinate.latitude;
    float _lon = location.coordinate.longitude;
    
    // Add a set of 2D and 3D POIs
    if( [self addPOI:[[CLLocation alloc]initWithLatitude:_lat - 1 longitude:_lon + 1]] &&
       
       [self addPOI:[[CLLocation alloc]initWithLatitude:_lat + 1 longitude:_lon + 1]])
        
    {
        if ( [self addPOI2D:[[CLLocation alloc]initWithLatitude:_lat + 1 longitude:_lon - 1]] &&
             [self addPOI2D:[[CLLocation alloc]initWithLatitude:_lat + 1 longitude:_lon - 2]] )
        {
            return YES;
        }
    }
    
    return NO;
    
}

- (BOOL)addPOI2D:(CLLocation*)location
{
    static int _counter2D = 0;
    
    //// CONFIGURE 2D POIS
    Poi2D* poi = [[Poi2D alloc] init];
    
    poi.altitude = 0;
    
    poi.selectedAlpha = 1;
    
    poi.notSelectedAlpha = .7;
    
    poi.poiSize = 5;
    
    [poi setLocation:location];
    
    switch (_counter2D) {
        case 0:
        {
            [poi setTextureSelectionPath:@"Viking_alpha.png"];
            [poi setTextureNonSelectionPath:@"Transformer_alpha.png"];
            break;
        }
        case 1:
        {
            [poi setTextureSelectionPath:@"Zombie.png"];
            [poi setTextureNonSelectionPath:@"Tv_alpha.png"];
            break;
        }
        default:
            break;
    }
    
    [_poisArray addObject:poi];
    
    // Add POI and get its unique id
    NSInteger uIdPOI = [my3dBrowser add:poi];
    
    _counter2D++;
    
    if (_counter2D == 2)
        _counter2D = 0;
    
    return uIdPOI!= -1 ? YES : NO;
}

- (BOOL)addPOI:(CLLocation*)location
{
    static int _counter = 0;
    
    Poi3D* poi = [[Poi3D alloc] init];
    
    poi.playAnimationOnStart = YES;
    
    poi.altitude = 0;
    
    poi.poiSize = 2;
    
    poi.poiCam =  POINTING_CAMERA;
    
    [poi setLocation:location];
    
    [_poisArray addObject:poi];
    
    if(_counter % 2 == 0)
    {
        poi.pathEAD = @"data/Models/pois/knight/Dark_knight.EAD";
        [poi setPoiSize:3];
    }
    else
    {
        poi.pathEAD = @"data/Models/pois/zombie/Zombie_head.EAD";
        [poi setPoiSize:10];
    }
    
    NSInteger uIdPOI = [my3dBrowser add:poi];
    
    _counter++;
    
    if (_counter == 2)
        _counter = 0;
    
    return uIdPOI == -1 ? NO : YES;
}


#pragma mark - Gesture Management

- (void)addGestureEvents
{
    // PAN
    if(_panRecognizer == nil)
    {
        _panRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(move:)];
        [_panRecognizer setMinimumNumberOfTouches:1];
        [_panRecognizer setMaximumNumberOfTouches:1];
        [_panRecognizer setDelegate:self];
        [self.view addGestureRecognizer:_panRecognizer];
    }
    
    // PINCH
    if (_pinchRecognizer == nil)
    {
        _pinchRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(zoomPinch:)];
        [self.view addGestureRecognizer:_pinchRecognizer];
    }
    
    // ROTATION
    if(_rotationRecognizer)
    {
        _rotationRecognizer = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(spin:)];
        [self.view addGestureRecognizer:_rotationRecognizer];
    }
    
}

- (void)spin:(UIRotationGestureRecognizer *)gestureRecognizer {
    
    //CGFloat rotation = gestureRecognizer.rotation;
    //NSLog(@"Rotation: %f", rotation);
    
}

- (void)zoomPinch:(UIPinchGestureRecognizer *)recognizer
{
    //NSLog(@"Pinch scale: %f, velocity: %f", recognizer.scale, recognizer.velocity);
}

-(void)move:(UIPanGestureRecognizer *)recognizer
{
    [my3dBrowser spin3DPOI:recognizer];
}

- (void)removeGestures
{
    NSArray* gesturesArr = [self.view gestureRecognizers];
    
    if ([gesturesArr count] > 0)
    {
        [self.view removeGestureRecognizer:_panRecognizer];
        [self.view removeGestureRecognizer:_pinchRecognizer];
        [self.view removeGestureRecognizer:_rotationRecognizer];
    }
}


#pragma mark - Memory Management

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)releaseMemory
{
    locationManager             = nil;
    my3dBrowser                 = nil;
    my3dBrowser.delegate        = nil;
    
    currentSelectedPOI          = nil;
    
    // GESTURES
    _pinchRecognizer            = nil;
    _panRecognizer              = nil;
    _rotationRecognizer         = nil;
    
    // RADAR
    _poisArray                  = nil;
    _radarController            = nil;
}


#pragma mark - Motion Manager

- (void)initMotionManager
{
    if (motionManager == nil)
    {
        // Set up MotionManager
        motionManager = [[CMMotionManager alloc] init]; // motionManager is an instance variable
        
        motionManager.showsDeviceMovementDisplay    = YES; //calibration popup
        
        motionManager.accelerometerUpdateInterval   = 1.0 / kAccelerometerFrequency; // 100Hz
        motionManager.deviceMotionUpdateInterval    = 1.0 / kAccelerometerFrequency;
        
        [motionManager startAccelerometerUpdates];
        [motionManager startDeviceMotionUpdatesUsingReferenceFrame:CMAttitudeReferenceFrameXMagneticNorthZVertical];
    }
}

- (void)removeMotionManager
{
    if (motionManager != nil)
    {
        [motionManager stopAccelerometerUpdates];
        [motionManager stopDeviceMotionUpdates];
        motionManager = nil;
    }
}


#pragma mark - Location Manager

- (void)setupLocationManager
{
    // LOCATION
    if (locationManager == nil)
    {
		locationManager = [[CLLocationManager alloc] init];
        locationManager.headingFilter = kCLHeadingFilterNone;
		locationManager.desiredAccuracy = kCLLocationAccuracyBest;
		locationManager.delegate = self;
        
        if ( [locationManager respondsToSelector:@selector(requestAlwaysAuthorization)] )
        {
            [locationManager requestAlwaysAuthorization];
        }
        
		[locationManager startUpdatingLocation];
        [locationManager startUpdatingHeading];
	}
}

-(void)removeLocationManager
{
    if (locationManager != nil)
    {
        [locationManager stopUpdatingHeading];
        locationManager = nil;
        lastLocation = nil;
    }
}


#pragma mark - Location Delegate

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
    NSLog(@"location error");
}

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation
{
    CLLocationDistance distanceInMeters = [newLocation distanceFromLocation:oldLocation];
    
    if(my3dBrowser != nil && distanceInMeters >= 0)
    {
        if (lastLocation == nil)
        {
            // Add POIs
            [self addPOIs:newLocation];
            
            [self refreshPois];
        }
        lastLocation = newLocation;
        
        NSLog(@"location updated lon %f and lat %f", newLocation.coordinate.longitude, newLocation.coordinate.latitude);
        
        // ARBrowser
        [my3dBrowser updateLocation:newLocation];
        
        // Radar
        [self setUserLocationInRadar:newLocation];
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
{
    [_radarController setHeading:newHeading];
}


#pragma mark - Render Delegate

- (void)poiClicked:(Poi *)poi
{
    NSLog(@"Poi %ld clicked!!!", (long)poi.uId);
    
    // Let's refresh the texture on click
    if ( [poi isKindOfClass:[Poi2D class]])
    {
        [(Poi2D*)poi setTextureSelectionPath:@"Knight_fullbody.png"];
        
        [my3dBrowser refreshPoiTextures:(Poi2D*)poi];
    }
    
    currentSelectedPOI = poi;
}

- (void)poiSelected:(Poi *)poi
{
    NSLog(@"Poi %ld selected!!!", (long)poi.uId);
    
    currentSelectedPOI = poi;
}

- (void)poisInView:(NSMutableArray *)poisArray
{
    //NSLog(@"Pois in view %d", [poisArray count]);
    [_radarController setSelectedPoi:currentSelectedPOI];
    [_radarController refresh];
}


#pragma mark - Camera management

- (void)initCapture {
	
    // init capture manager
    _captureManager = [[CaptureSessionManager alloc] init];
    
    // set video streaming quality
    _captureManager.captureSession.sessionPreset = AVCaptureSessionPresetMedium;   //480x360
    
    [_captureManager setOutPutSetting:[NSNumber numberWithInt:kCVPixelFormatType_32BGRA]]; //kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange
    
    [_captureManager addVideoInput:AVCaptureDevicePositionBack]; //AVCaptureDevicePositionFront / AVCaptureDevicePositionBack
    [_captureManager addVideoOutput];
    [_captureManager addVideoPreviewLayer];
    
    CGRect layerRect = self.view.bounds;
    
    [[_captureManager previewLayer] setOpaque: 0];
    [[_captureManager previewLayer] setBounds:layerRect ];
    [[_captureManager previewLayer] setPosition:CGPointMake( CGRectGetMidX(layerRect), CGRectGetMidY(layerRect) ) ];
    
    // create a view, on which we attach the AV Preview layer
    _cameraView = [[UIView alloc] initWithFrame:self.view.bounds];
    [[_cameraView layer] addSublayer:[_captureManager previewLayer]];
    
    // add the view we just created as a subview to the View Controller's view
    [self.view addSubview: _cameraView];
    
    // start !
    [self performSelectorInBackground:@selector(start_captureManager) withObject:nil];
    
}

- (void)removeCapture
{
    [_captureManager.captureSession stopRunning];
    [_cameraView removeFromSuperview];
    _captureManager     = nil;
    _cameraView         = nil;
}

- (void)start_captureManager
{
    @autoreleasepool
    {
        [[_captureManager captureSession] startRunning];
    }
}


#pragma mark - Radar

- (void)setupRadar
{
    if (_radarController == nil)
    {
        _radarController = [[PoiRadarController alloc] initWithKey:@"cffd9090c2d30af63325a5e4faeb795edd8bf12d"];
        
        UIImage* radarImage;
        
        if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
        {
            radarImage = [UIImage imageNamed:@"resources.bundle/iPhoneRadar.png"];
        }else{
            radarImage = [UIImage imageNamed:@"resources.bundle/iPadRadar.png"];
        }
        
        [_radarController.view setFrame:CGRectMake(self.view.frame.origin.x + 10, self.view.frame.origin.y + 10, radarImage.size.width, radarImage.size.height)];
        
        [_radarController setRadarImage:radarImage];
        
        [_radarController setPoiImage:[UIImage imageNamed:@"resources.bundle/poi.png"]];
        [_radarController setPoiImageSelected:[UIImage imageNamed:@"resources.bundle/poiSelected.png"]];
        [_radarController setNorthImage:[UIImage imageNamed:@"resources.bundle/northRadar.png"]];
        
        [self.view addSubview:_radarController.view];
    }
}

- (void)removeRadar
{
    [_radarController.view removeFromSuperview];
    _radarController    = nil;
}

-(void)rotateRadarView:(double)degrees
{
    [_radarController rotateRadarView:degrees];
}

-(void) refreshPois
{
    @synchronized(self)
    {
        [_radarController setPoisArray:_poisArray];
        [_radarController reset];
        [_radarController refresh];
    }
}

-(void)setUserLocationInRadar:(CLLocation *)_userLocation
{
    [_radarController setUserLocation:_userLocation];
}


#pragma mark - Autorotate

- (BOOL)shouldAutorotate
{
    return NO;
}

#pragma mark - Util functions

-(UIColor*)colorWithHexString:(NSString*)hex
{
    NSString *cString = [[hex stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    
    // String should be 6 or 8 characters
    if ([cString length] < 6) return [UIColor grayColor];
    
    // strip 0X if it appears
    if ([cString hasPrefix:@"0X"]) cString = [cString substringFromIndex:2];
    
    if ([cString length] != 6) return  [UIColor grayColor];
    
    // Separate into r, g, b substrings
    NSRange range;
    range.location = 0;
    range.length = 2;
    NSString *rString = [cString substringWithRange:range];
    
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    
    // Scan values
    unsigned int r, g, b;
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    
    return [UIColor colorWithRed:((float) r / 255.0f)
                           green:((float) g / 255.0f)
                            blue:((float) b / 255.0f)
                           alpha:1.0f];
}

@end
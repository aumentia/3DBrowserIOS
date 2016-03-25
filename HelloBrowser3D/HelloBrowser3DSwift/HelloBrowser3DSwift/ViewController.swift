//
//  ViewController.swift
//  HelloBrowser3DSwift
//
//  Created by Pablo GM on 11/09/15.
//  Copyright © 2015 Aumentia Technologies SL. All rights reserved.
//

let kAccelerometerFrequency = 90.0     //Hz

import UIKit

class ViewController: UIViewController, EDBrowserProtocol
{
    // Location manager instance
    var _locationManager:CLLocationManager!
    
    // Browser instance
    var _my3dBrowser:_DBrowser!
    
    // Gestures
    var _panRecognizer:UIPanGestureRecognizer!
    var _pinchRecognizer:UIPinchGestureRecognizer!
    var _rotationRecognizer:UIRotationGestureRecognizer!
    
    // Camera
    var _captureManager:CaptureSessionManager!
    var _cameraView:UIView!
    
    // Radar Plugin
    var _radarController:PoiRadarController!
    var _poisArray:NSMutableArray!
    
    // Motion
    var _motionManager:CMMotionManager!
    
    var _currentSelectedPOI:Poi!
    
    var _lastLocation:CLLocation!
    
    

    // MARK: - View Life Cycle
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewWillAppear(animated: Bool)
    {
        super.viewWillAppear(animated)
        
        // Add camera
        initCapture()
        
        // Initialize
        _my3dBrowser = _DBrowser(browser: self.view.bounds, withKey: "7b62a465ea1965171a81aed536b313c62e290478", setDebug: false, representation: poiRepresentation.geographical)
        
        assert(_my3dBrowser != nil, "Check API Key")
        
        // Delegate
        _my3dBrowser.delegate = self
        
        // Transparent background
        _my3dBrowser.backgroundColor = UIColor.clearColor()
        
        // Add view
        self.view.addSubview(_my3dBrowser)
        self.view.bringSubviewToFront(_my3dBrowser)
        
        // Add gestures
        addGestureEvents()
        
        // Init location manager
        setupLocationManager()
        
        // Init motion
        initMotionManager()
        _my3dBrowser.setMotionManager(_motionManager)
        
        // Radar
        _poisArray = NSMutableArray()
        setupRadar()
        
        self.view.backgroundColor = UIColor.clearColor()
    }
    
    override func viewWillDisappear(animated: Bool)
    {
        super.viewWillDisappear(animated)
        
        // Remove POIs
        _my3dBrowser.removeAllPois()
        
        // Remove camera
        removeCapture()
        
        // Remove gestures
        removeGestures()
        
        // Remove motion manager
        removeMotionManager()
        
        // Remove location manager
        removeLocationManager()
        
        // Remove radar
        removeRadar()
        
        // Release memory
        _my3dBrowser.releaseBrowser()
        _my3dBrowser.removeFromSuperview()
        releaseMemory()
    }

    
    // MARK: - Memory Management
    
    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func releaseMemory()
    {
        _locationManager        = nil
        _my3dBrowser            = nil
        _my3dBrowser.delegate   = nil
        
        _currentSelectedPOI     = nil
        
        // GESTURES
        _pinchRecognizer        = nil
        _panRecognizer          = nil
        _rotationRecognizer     = nil
        
        // RADAR
        _poisArray.removeAllObjects()
        _poisArray              = nil
        _radarController        = nil
    }
}


// MARK: - 3D Browser
extension ViewController
{
    // MARK: - Add POIs
    
    func addPoi(location: CLLocation) -> Bool
    {
        struct Counter { static var _counter = 0 }
        
        let poi:Poi3D =  Poi3D()
        
        poi.playAnimationOnStart = true
        
        poi.altitude = 0
        
        poi.poiSize  = 2
        
        poi.poiCam   = poi_camera.POINTING_CAMERA
        
        poi.location = location
        
        _poisArray.addObject(poi)
        
        if Counter._counter % 2 == 0
        {
            poi.pathEAD = "data/Models/pois/knight/Dark_knight.EAD"
            poi.poiSize = 3
        }
        else
        {
            poi.pathEAD = "data/Models/pois/zombie/Zombie_head.EAD"
            poi.poiSize = 10
        }
        
        let uIdPOI = _my3dBrowser.add(poi)
        
        Counter._counter += 1
        
        if Counter._counter == 2
        {
            Counter._counter = 0
        }
        
        return uIdPOI == -1 ? false : true
    }
    
    func addPoi2D(location: CLLocation) -> Bool
    {
        struct Counter2D { static var _counter2D = 0 }
        
        let poi:Poi2D   = Poi2D()
        
        poi.altitude    = 0
        
        poi.setSelectedAlpha(1.0)
        
        poi.setNotSelectedAlpha(0.7)
        
        poi.poiSize     = 5
        
        poi.location    = location
        
        switch (Counter2D._counter2D)
        {
            case 0:
                poi.setTextureSelectionPath(NSString(string: "Viking_alpha.png") as String)
                poi.setTextureNonSelectionPath(NSString(string: "Transformer_alpha.png") as String)
                break
            case 1:
                poi.setTextureSelectionPath(NSString(string: "Zombie.png") as String)
                poi.setTextureNonSelectionPath(NSString(string: "Tv_alpha.png") as String)
                break
            default:
                break
        }
        
        _poisArray.addObject(poi)
        
        let uIdPOI = _my3dBrowser.add(poi)
        
        Counter2D._counter2D += 1
        
        if Counter2D._counter2D == 2
        {
            Counter2D._counter2D = 0
        }
        
        return uIdPOI == -1 ? false : true
    }
    
    func addPois(location: CLLocation) -> Bool
    {
        let _lat = location.coordinate.latitude
        let _lon = location.coordinate.longitude
        
        // Add a set of 2D and 3D POIs
        if addPoi(CLLocation(latitude: _lat - 1, longitude: _lon + 1)) && addPoi(CLLocation(latitude: _lat + 1, longitude: _lon + 1))
        {
            if addPoi2D(CLLocation(latitude: _lat + 1, longitude: _lon - 1)) && addPoi2D( CLLocation(latitude: _lat + 1, longitude: _lon - 2))
            {
                return true
            }
        }
        return false
    }
    
    
    // MARK: - Radar
    
    func setupRadar()
    {
        if _radarController == nil
        {
            _radarController = PoiRadarController(key: "67986b617b130cbf79bb0becd800c0a2a5fed428")
            
            assert(_radarController != nil, "Check API Key")
            
            var radarImage:UIImage
            
            if UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiom.Phone
            {
                radarImage = UIImage(named: "resources.bundle/iPhoneRadar.png")!
            }
            else
            {
                radarImage = UIImage(named: "resources.bundle/iPadRadar.png")!
            }
            
            _radarController.view.frame = CGRectMake(self.view.frame.origin.x + 10, self.view.frame.origin.y + 10, radarImage.size.width, radarImage.size.height)
            
            _radarController.radarImage = radarImage
            
            _radarController.poiImage           = UIImage(named: "resources.bundle/poi.png")
            _radarController.poiImageSelected   = UIImage(named: "resources.bundle/poiSelected.png")
            _radarController.northImage         = UIImage(named: "resources.bundle/northRadar.png")
            
            self.view.addSubview(_radarController.view)
        }
    }
    
    func removeRadar()
    {
        _radarController.view.removeFromSuperview()
        _radarController = nil
    }
    
    func rotateRadarView(degrees:Double)
    {
        _radarController.rotateRadarView(degrees)
    }
    
    func refreshPois()
    {
        let lockQueue = dispatch_queue_create("com.aumentia.LockQueue", nil)
        dispatch_sync(lockQueue)
            {
                self._radarController.poisArray = self._poisArray
                self._radarController.reset()
                self._radarController.refresh()
        }
    }
    
    func setUserLocationInRadar(userLocation:CLLocation)
    {
        _radarController.userLocation = userLocation
    }
    
    
    // MARK: - Render Delegate
    
    func poiClicked(poi: Poi!)
    {
        print("Poi \(poi.uId) clicked!!!")
        
        // Let's refresh the texture on click
        if let p = poi as? Poi2D
        {
            p.setTextureSelectionPath(NSString(string: "Knight_fullbody.png") as String)
            
            _my3dBrowser.refreshPoiTextures(p)
        }
        
        _currentSelectedPOI = poi
    }
    
    func poiSelected(poi: Poi!)
    {
        print("Poi \(poi.uId) selected!!!")
        
        _currentSelectedPOI = poi
    }
    
    func poisInView(poisArray: NSMutableArray!)
    {
        _radarController.selectedPoi = _currentSelectedPOI
        _radarController.refresh()
    }
}


// MARK: - Camera management
extension ViewController
{
    func initCapture()
    {
        // Init capture manager
        _captureManager = CaptureSessionManager()
        
        // Set video streaming quality
        _captureManager.captureSession.sessionPreset = AVCaptureSessionPresetPhoto
        
        _captureManager.outPutSetting = NSNumber(unsignedInt: kCVPixelFormatType_32BGRA)
        
        _captureManager.addVideoInput(AVCaptureDevicePosition.Back)
        _captureManager.addVideoOutput()
        _captureManager.addVideoPreviewLayer()
        
        let layerRect:CGRect = self.view.bounds
        
        _captureManager.previewLayer.opaque = false
        _captureManager.previewLayer.bounds = layerRect
        _captureManager.previewLayer.position = CGPointMake(CGRectGetMidX(layerRect), CGRectGetMidY(layerRect))
        
        // Create a view where we attach the AV Preview Layer
        _cameraView = UIView(frame: self.view.bounds)
        _cameraView.layer .addSublayer(_captureManager.previewLayer)
        
        // Add the view we just created as a subview to the View Controller's view
        self.view.addSubview(_cameraView)
        
        // Start
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0))
            {
                self.startCaptureManager()
        }
    }
    
    func removeCapture()
    {
        _captureManager.captureSession.stopRunning()
        _cameraView.removeFromSuperview()
        _captureManager = nil
        _cameraView     = nil
    }
    
    func startCaptureManager()
    {
        autoreleasepool
            {
                _captureManager.captureSession.startRunning()
        }
    }
}


// MARK: - Motion Manager
extension ViewController
{
    func initMotionManager()
    {
        if _motionManager == nil
        {
            // Setup MotionManager
            _motionManager = CMMotionManager()
            
            _motionManager.showsDeviceMovementDisplay  = true
            
            _motionManager.accelerometerUpdateInterval = 1.0 / kAccelerometerFrequency
            _motionManager.deviceMotionUpdateInterval  = 1.0 / kAccelerometerFrequency
            
            _motionManager.startAccelerometerUpdates()
            _motionManager.startDeviceMotionUpdatesUsingReferenceFrame(CMAttitudeReferenceFrame.XMagneticNorthZVertical)
        }
    }
    
    func removeMotionManager()
    {
        if _motionManager != nil
        {
            _locationManager.stopUpdatingHeading()
            _locationManager.stopUpdatingLocation()
            _locationManager = nil
            _lastLocation    = nil
        }
    }
}


// MARK: - Gesture Management
extension ViewController:UIGestureRecognizerDelegate
{
    func addGestureEvents()
    {
        // PAN
        if _panRecognizer == nil
        {
            _panRecognizer = UIPanGestureRecognizer(target: self, action: #selector(ViewController.move(_:)))
            _panRecognizer.minimumNumberOfTouches = 1
            _panRecognizer.maximumNumberOfTouches = 1
            _panRecognizer.delegate               = self
            
            self.view.addGestureRecognizer(_panRecognizer)
        }
        
        // PINCH
        if _pinchRecognizer == nil
        {
            _pinchRecognizer = UIPinchGestureRecognizer(target: self, action: #selector(ViewController.zoomPinch(_:)))
            
            self.view.addGestureRecognizer(_pinchRecognizer)
        }
        
        // ROTATION
        if _rotationRecognizer == nil
        {
            _rotationRecognizer = UIRotationGestureRecognizer(target: self, action: #selector(ViewController.spin(_:)))
            
            self.view.addGestureRecognizer(_rotationRecognizer)
        }
    }
    
    @objc func spin(recognizer:UIRotationGestureRecognizer)
    {
        
    }
    
    @objc func zoomPinch(recognizer:UIPinchGestureRecognizer)
    {
        
    }
    
    @objc func move(recognizer:UIPanGestureRecognizer)
    {
        _my3dBrowser.spin3DPOI(recognizer)
    }
    
    func removeGestures()
    {
        if _panRecognizer != nil
        {
            self.view.removeGestureRecognizer(_panRecognizer)
        }
        if _pinchRecognizer != nil
        {
            self.view.removeGestureRecognizer(_pinchRecognizer)
        }
        if _rotationRecognizer != nil
        {
            self.view.removeGestureRecognizer(_rotationRecognizer)
        }
    }
}


// MARK: - Location Manager
extension ViewController: CLLocationManagerDelegate
{
    func setupLocationManager()
    {
        if _locationManager == nil
        {
            _locationManager                    = CLLocationManager()
            _locationManager.headingFilter      = kCLHeadingFilterNone
            _locationManager.desiredAccuracy    = kCLLocationAccuracyBest
            _locationManager.delegate           = self
            
            if _locationManager.respondsToSelector(#selector(CLLocationManager.requestWhenInUseAuthorization))
            {
                _locationManager.requestWhenInUseAuthorization()
            }
            
            _locationManager.startUpdatingLocation()
            _locationManager.startUpdatingHeading()
        }
    }
    
    func removeLocationManager()
    {
        if _locationManager != nil
        {
            _locationManager.stopUpdatingHeading()
            _locationManager.stopUpdatingLocation()
        }
    }
    
    
    // MARK: - Location Delegate
    
    func locationManager(manager: CLLocationManager, didFailWithError error: NSError)
    {
        print("Error: " + error.description)
    }
    
    func locationManager(manager: CLLocationManager, didUpdateHeading newHeading: CLHeading)
    {
        _radarController.setHeading(newHeading)
    }
    
    func locationManager(manager: CLLocationManager, didUpdateToLocation newLocation: CLLocation, fromLocation oldLocation: CLLocation)
    {
        let distanceInMeters:CLLocationDistance = newLocation.distanceFromLocation(oldLocation)
        
        if _my3dBrowser != nil && distanceInMeters >= 0
        {
            if _lastLocation == nil
            {
                // Add POIs
                addPois(newLocation)
                
                refreshPois()
            }
            _lastLocation = newLocation
            
            print("Location updated: lon \(newLocation.coordinate.longitude) and lat \(newLocation.coordinate.latitude)")
            
            // ARBrowser
            _my3dBrowser.updateLocation(newLocation)
            
            // Radar
            setUserLocationInRadar(newLocation)
        }
    }
}


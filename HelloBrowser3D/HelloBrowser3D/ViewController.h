//
//  ViewController.h
//
//  Hello3DBrowser
//
//  Copyright (c) 2015 Aumentia. All rights reserved.
//
//  Written by Pablo GM <info@aumentia.com>, January 2015
//

#import <UIKit/UIKit.h>

#import <ARBrowser3D/3DBrowser.h>
#import <ARB3D_radar_1/PoiRadarController.h>

@interface ViewController : UIViewController<CLLocationManagerDelegate, EDBrowserProtocol, UIGestureRecognizerDelegate, UIAccelerometerDelegate>
{
    CLLocationManager *locationManager;
}

@property (nonatomic, strong) CLLocationManager *locationManager;

@end
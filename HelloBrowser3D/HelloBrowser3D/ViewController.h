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

#import <ARBrowser3D/ARBrowser3D.h>
#import <ARBrowser3DRadar/ARBrowser3DRadar.h>

@interface ViewController : UIViewController<CLLocationManagerDelegate, EDBrowserProtocol, UIGestureRecognizerDelegate, UIAccelerometerDelegate>
{
    CLLocationManager *locationManager;
}

@property (nonatomic, strong) CLLocationManager *locationManager;

@end
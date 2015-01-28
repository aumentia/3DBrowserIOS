//
//  CaptureSessionManager.h
//
//  Hello3DBrowser
//
//  Copyright (c) 2015 Aumentia. All rights reserved.
//
//  Written by Pablo GM <info@aumentia.com>, January 2015
//


#import <CoreMedia/CoreMedia.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>


@interface CaptureSessionManager : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>
{
    
}

@property (strong,nonatomic) AVCaptureVideoPreviewLayer     *previewLayer;
@property (strong,nonatomic) AVCaptureSession               *captureSession;
@property (strong,nonatomic) AVCaptureStillImageOutput      *stillImageOutput;
@property (strong,nonatomic) UIImage                        *stillImage;
@property (strong,nonatomic) NSNumber                       *outPutSetting;

/**
 *  @brief Add video input: front or back camera:
 *  AVCaptureDevicePositionBack
 *  AVCaptureDevicePositionFront
 */
- (void)addVideoInput:(AVCaptureDevicePosition)_campos;

/**
 *  @brief Add video output
 */
- (void)addVideoOutput;

/**
 *  @brief Add preview layer
 */
- (void)addVideoPreviewLayer;

@end
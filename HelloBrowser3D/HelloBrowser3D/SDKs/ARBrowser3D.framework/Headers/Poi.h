/*************************************************************************
 *
 * AUMENTIA TECHNOLOGIES
 * __________________
 *
 *  Copyright Aumentia Technologies. All rights reserved 2015.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Aumentia Technologies and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Aumentia Technologies
 * and its suppliers and may be covered by Spain and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Aumentia Technologies.
 *
 * File: Poi.h
 * Description:
 * Author: Pablo GM (info@aumentia.com)
 * Created: 23/01/15.
 * Verion 1.0
 *
 *
 **************************************************************************/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "_3DBrowser_versions.h"

/**
 @brief The POI (point of interest) is the basic unit that represents an item in the 3DBrowser.
 *      It can be 2D or 3D.
 */
__attribute__((__visibility__("default"))) @interface Poi : NSObject
{
    @public
    
    /**
     @brief _altitude: Height of the poi. Values between -90 and 90.
     */
    CGFloat _altitude;
    
    /**
     @brief _location: coordinates of the poi
     */
    CLLocation* _location;
    
    /**
     @brief _locationc: cardinal location
     */
    CGPoint _locationc;
    
    /**
     @brief _uId: unique ID of the POI
     */
    NSInteger _uId;
    
    /**
     @brief _poiSize: POI size
     */
    CGFloat _poiSize;

    @private
    
    /**
     @brief _modelId: model ID of the POI
     */
    NSInteger _modelId;
    
    /**
     @brief _meshId: mesh ID of the POI
     */
    NSInteger _meshId;
    
    /**
     @brief _cloneId: clone ID of the POI
     */
    NSInteger _cloneId;
    
    /**
     @brief _eadId: EAD ID of the POI
     */
    NSInteger _eadId;
    
    /**
     @brief _controllerId: controller ID of the POI
     */
    NSInteger _controllerId;
    
    /**
     @brief _animationList: list of animations of the POI
     */
    NSMutableArray *_animationList;
    
}

@property (nonatomic, assign) CGFloat               altitude;
@property (nonatomic, strong) CLLocation            *location;
@property CGPoint                                   locationc;
@property NSInteger                                 uId;
@property NSInteger                                 modelId;
@property NSInteger                                 meshId;
@property NSInteger                                 cloneId;
@property NSInteger                                 eadId;
@property NSInteger                                 controllerId;
@property (nonatomic, strong) NSMutableArray        *animationList;
@property CGFloat                                   poiSize;

/**
 @brief Initialize Poi
 */
-(id) init AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

@end
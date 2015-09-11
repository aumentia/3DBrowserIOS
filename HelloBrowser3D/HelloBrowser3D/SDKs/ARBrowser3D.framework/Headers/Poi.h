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
 * Verion 1.1
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
    
    
    CGFloat _altitude;
    
    
    CLLocation* _location;
    
    
    CGPoint _locationc;
    
    
    NSInteger _uId;
    
    CGFloat _poiSize;

    @private
    
    
    NSInteger _modelId;
    
    
    NSInteger _meshId;
    
    
    NSInteger _cloneId;
    
    
    NSInteger _eadId;
    
    
    NSInteger _controllerId;
    
    
    NSMutableArray *_animationList;
    
}

/**
 @brief altitude Height of the poi. Values between -90 and 90.
 */
@property (nonatomic, assign) CGFloat               altitude;
/**
 @brief location coordinates of the poi
 */
@property (nonatomic, strong) CLLocation            *location;
/**
 @brief locationc cardinal location
 */
@property CGPoint                                   locationc;
/**
 @brief uId unique ID of the POI
 */
@property NSInteger                                 uId;
/**
 @brief modelId model ID of the POI
 */
@property NSInteger                                 modelId;
/**
 @brief meshId mesh ID of the POI
 */
@property NSInteger                                 meshId;
/**
 @brief cloneId clone ID of the POI
 */
@property NSInteger                                 cloneId;
/**
 @brief eadId EAD ID of the POI
 */
@property NSInteger                                 eadId;
/**
 @brief controllerId controller ID of the POI
 */
@property NSInteger                                 controllerId;
/**
 @brief animationList list of animations of the POI
 */
@property (nonatomic, strong) NSMutableArray        *animationList;
/**
 @brief poiSize POI size
 */
@property CGFloat                                   poiSize;

/**
 @brief Initialize Poi
 */
-(id) init AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

@end
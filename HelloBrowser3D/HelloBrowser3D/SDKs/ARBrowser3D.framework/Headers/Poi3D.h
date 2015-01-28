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
 * File: Poi3D.h
 * Description:
 * Author: Pablo GM (info@aumentia.com)
 * Created: 23/01/15.
 * Verion 1.0
 *
 *
 **************************************************************************/


#import "Poi.h"

typedef enum
{
    FACING_CAMERA,
    POINTING_CAMERA,
    NONE,
    FACING_SELECTED_POI,
    FACING_SELECTED_POI_WHILE_MOVING,
    FACING_ORIGIN_POI,
    FACING_ORIGIN_POI_WHILE_MOVING
}poi_camera;

/**
 @brief 3D Poi needs to be exported from 3D Max or Maya using the plugins for those softwares.
 */

__attribute__((__visibility__("default"))) @interface Poi3D : Poi
{
    @public
    
    /**
     @brief _pathEAD: list of animations of the POI
     */
    NSString *_pathEAD;
    
    /**
     @brief _playAnimationOnStart: play animation just when adding the POI
     */
    BOOL _playAnimationOnStart;
    
    /**
     @brief _poiCam: POI initial lookAt: facing the camera, pointing the camera or default as the artist design it
     */
    poi_camera _poiCam;
    
    @private
    
    /**
     @brief _localModelMatrix: initial local model matrix
     */
    NSMutableArray *_localModelMatrix;
    
    /**
     @brief _lastAccX: last acceleration on X axis
     */
    CGFloat _lastAccX;
    
    /**
     @brief _lastAccY: last acceleration on Y axis
     */
    CGFloat _lastAccY;
    
}

@property (nonatomic, strong) NSString              *pathEAD;
@property (nonatomic, assign) BOOL                  playAnimationOnStart;
@property poi_camera                                poiCam;
@property (nonatomic, strong) NSMutableArray        *localModelMatrix;
@property (nonatomic, assign) CGFloat               lastAccX;
@property (nonatomic, assign) CGFloat               lastAccY;

@end
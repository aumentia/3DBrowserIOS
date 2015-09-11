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
 * Verion 1.1
 *
 *
 **************************************************************************/


#import "Poi.h"


typedef NS_ENUM(NSInteger, poi_camera) {
    /**
     * POI faces the camera
     */
    FACING_CAMERA,
    /**
     * POI points to camera
     */
    POINTING_CAMERA,
    /**
     * Default
     */
    NONE,
    /**
     * POI faces the selected POI
     */
    FACING_SELECTED_POI,
    /**
     * POI faces the selected POI only while moving
     */
    FACING_SELECTED_POI_WHILE_MOVING,
    /**
     * POI faces the origin
     */
    FACING_ORIGIN_POI,
    /**
     * POI faces the origin only while moving
     */
    FACING_ORIGIN_POI_WHILE_MOVING
};

/**
 @brief 3D Poi needs to be exported from 3D Max or Maya using the plugins for those softwares.
 */

__attribute__((__visibility__("default"))) @interface Poi3D : Poi
{
    @public
    
    
    NSString *_pathEAD;
    
    
    BOOL _playAnimationOnStart;
    
    
    poi_camera _poiCam;
    
    @private
    
    
    NSMutableArray *_localModelMatrix;
    
   
    CGFloat _lastAccX;
    
    
    CGFloat _lastAccY;
    
}
/**
 @brief pathEAD list of animations of the POI
 */
@property (nonatomic, strong) NSString              *pathEAD;
/**
 @brief playAnimationOnStart play animation just when adding the POI
 */
@property (nonatomic, assign) BOOL                  playAnimationOnStart;
/**
 @brief poiCam: POI initial lookAt facing the camera, pointing the camera or default as the artist design it
 */
@property poi_camera                                poiCam;
/**
 @brief localModelMatrix initial local model matrix
 */
@property (nonatomic, strong) NSMutableArray        *localModelMatrix;
/**
 @brief lastAccX last acceleration on X axis
 */
@property (nonatomic, assign) CGFloat               lastAccX;
/**
 @brief lastAccY last acceleration on Y axis
 */
@property (nonatomic, assign) CGFloat               lastAccY;

@end
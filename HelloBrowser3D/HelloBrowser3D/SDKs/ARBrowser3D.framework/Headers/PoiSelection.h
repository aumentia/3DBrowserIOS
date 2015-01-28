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
 * File: PoiSelection.h
 * Description:
 * Author: Pablo GM (info@aumentia.com)
 * Created: 23/01/15.
 * Verion 1.0
 *
 *
 **************************************************************************/


#import "Poi3D.h"

/**
 * @brief animation done when doing the transition between POIs
 *
 * ANIM_ON:  animation POI is playing all the time.
 * ANIM_OFF: animation POI is not playing at all.
 * ANIM_ON_WHILE_MOVING: animation POI is playing while moving and stop when reach the selected POI.
 */
typedef enum  {
    ANIM_ON,
    ANIM_OFF,
    ANIM_ON_WHILE_MOVING
}animationMode;

/**
 @brief Represents special type of 3D POI used to represent animation between POIs selected
 */
@interface PoiSelection : Poi3D {
    /**
     @brief _animationSpeed: transition speed
     */
    NSInteger       _animationSpeed;
    /**
     @brief _followPath: if true the animation POI follows line between points, if false, the animation POI just appear over the target POI
     */
    BOOL            _followPath;
    
    /**
     @brief _animMode: animation mode. Modes available {@link PoiSet.animationMode}
     */
    animationMode   _animMode;
    
    /**
     @brief _isAnimationMoving: if animMode is not OFF, the POI will move from initial position to final position following a straight line.
     * This flags is set to YES will the POI is moving.
     */
    BOOL            _isAnimationMoving;
    
}

@property (nonatomic, assign) NSInteger     animationSpeed;
@property (nonatomic, assign) BOOL          followPath;
@property (nonatomic, assign) animationMode animMode;
@property (nonatomic, assign) BOOL          isAnimationMoving;

@end
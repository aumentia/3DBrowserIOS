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
 * File: 3DBrowser.h
 * Description:
 * Author: Pablo GM (info@aumentia.com)
 * Created: 23/01/15.
 * Verion 1.1
 *
 *
 **************************************************************************/


#import <UIKit/UIKit.h>
#import "Poi.h"
#import "Poi2D.h"
#import "Poi3D.h"
#import "PoiSelection.h"
#import <CoreMotion/CoreMotion.h>
#import "EAGLView.h"


typedef NS_ENUM(NSInteger, connType) {
    /**
     * Synchronously
     */
    SYNC,
    /**
     * Asynchronously
     */
    ASYNC,
};

/**
 * Way of representing the POI
 */
typedef NS_ENUM(NSInteger, poiRepresentation) {
    /**
     * Geographical representation
     */
    geographical,
    /**
     * Cartesian representation
     */
    cartensian,
};

/**
 * 3D Browser protocol
 */
@protocol EDBrowserProtocol <NSObject, NSURLConnectionDelegate>

@optional

/**
 @brief Callback called when a POI is touched
 @param poi the POI touched
 */
-(void) poiClicked:(Poi*)poi ;

/**
 @brief Callback called when the device in pointing in direction of a POI
 @param poi the pointed-at poi
 */
-(void) poiSelected:(Poi*)poi ;

/**
 @brief Callback that returns the current POIs in the view ordered by distance from the center of the screen to the sides.
 @param poisArray Array with the POIs in view. Empty if there are no POIs
 */
-(void) poisInView:(NSMutableArray*)poisArray;

/**
 @brief Called when the Poi selection / non selection texture has been loaded from URL
 @param poi the poi loaded
 */
-(void)poiTexturesLoadedFromURL:(Poi*)poi;

/**
 *  @brief Called each rendering frame.
 */
-(void) frameRendered;

@end

/**
 * 3D Browser main class
 */
__attribute__((__visibility__("default"))) @interface _DBrowser : UIView<
                                                                    UIGestureRecognizerDelegate,
                                                                    renderProtocol,
                                                                    CLLocationManagerDelegate>
{
    
}

/**
 * 3D Browser delegate instance
 */
@property (weak, nonatomic)  id <EDBrowserProtocol> delegate;


/*==================================================
 INIT & CONFIG
 ==================================================*/

/**
 * @brief Init 3D Browser instance
 * @param frame      3D Browser frame
 * @param key        license key provided
 * @param isDebug    display debug logs
 * @param representation POI representation
 * @return 3D Browser instance
 */
- (id)initBrowser:(CGRect)frame withKey:(NSString*)key setDebug:(BOOL)isDebug representation:(poiRepresentation)representation AR3DBrowser_AVAILABLE(AR3DBrowser_V_1_1);

/**
 * @brief Set the connection type to retrieve selection and non selection textures
 * @param connectionType     SYNC or ASYNC. Default ASYNC.
 * @param loading         Whether to display or not a loading while loading the textures ASYNC. Default NO.
 */
- (void)setUrlConnections:(connType)connectionType displayLoading:(BOOL)loading AR3DBrowser_AVAILABLE(AR3DBrowser_V_1_0);


/*==================================================
 ADD / REMOVE / GET POI Functions
 ==================================================*/

/**
 * @brief Adds POI
 * @param poi POI to be added
 * @return uId of the Poi added
 */
-(NSInteger) add:(Poi*) poi AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Adds POI
 * @param poi POI to be added
 * @param uId unique ID of the Poi to be added
 * @return YES if Poi successfuly added and the ID is unique.
 */
-(BOOL) add:(Poi*)poi withId:(NSInteger)uId AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Update user location in order to display the POIs accordingly
 * @param newuserLocation New user location
 */
-(void)updateLocation:(CLLocation *)newuserLocation AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Update user cardinal location in order to display the POIs accordingly
 * @param newuserLocationc New user location
 */
-(void)updateUserLocation:(CGPoint)newuserLocationc AR3DBrowser_AVAILABLE(AR3DBrowser_V_1_1);

/**
 * @brief Set motion manager
 * @param m motion manager instance
 */
-(void)setMotionManager:(CMMotionManager*)m;

/**
 * @brief Remove POI
 * @param poi POI to be removed
 * @return YES if Poi successfuly removed
 */
-(BOOL)remove:(Poi*)poi AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Remove POI
 * @param uId unique ID of the Poi to be removed
 * @return YES if Poi successfuly removed
 */
-(BOOL) removePoiWithId:(NSInteger)uId AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Remove all POIs
 * 
 */
-(void)removeAllPois AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Get POI
 * @param uId Unique id of the POI to retrieve
 * @return Poi 
 */
-(Poi*) getPoi:(NSInteger)uId AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Add reference icons in the 4 main cardinal points
 */
-(void) addPoleIcons AR3DBrowser_DEPRECATED(AR3DBrowser_V_1_0, AR3DBrowser_V_1_0) DEPRECATED_ATTRIBUTE;

/**
 * @brief Remove cardinal points reference icons
 * @return YES if successfully remove, NO otherwise
 */
-(BOOL) removePoleIcons AR3DBrowser_DEPRECATED(AR3DBrowser_V_1_0, AR3DBrowser_V_1_0) DEPRECATED_ATTRIBUTE;


/*==================================================
 PROPERTIES
 ==================================================*/

/**
 * @brief Set POI size
 * @param inPoi poi to change size.
 */
-(void)setPoiSize:(Poi*)inPoi AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Refresh poi texture
 * Use this function to change the texture on run time.
 * @param inPoi poi to refresh texture.
 */
-(void)refreshPoiTextures:(Poi2D*)inPoi AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Refresh poi alpha
 * Use this function to change the alpha of a poi on run time.
 * @param inPoi poi to refresh texture.
 */
-(void)refreshPoiAlpha:(Poi2D*)inPoi AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);


/*==================================================
        3D POI GESTURES
 ==================================================*/

/**
 * @brief Rotate 3D POI
 * @param recognizer   pan gesture
 */
-(void)spin3DPOI:(UIPanGestureRecognizer *)recognizer AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);


/*==================================================
        TRANSITON POI
 ==================================================*/

/**
 * @brief Set a selection model. he selection model is a POI that moves from the old selected POI to the new selected one.
 * @param modelPath 3D POI model path
 * @param poiCam    @link poi_camera type
 * @param animMode  @link animationMode type
 * @param animSpeed animation speed
 * @param followPath    if YES, the transition POI follows the 3D rect between old and new selected POIs. If NO, just moves from old POI's position to new POI's position.
 * @return BOOL         YES if selection POI properly configured, NO otherwise.
 */
-(BOOL)setPoiSelectionModel:(NSString*)modelPath withPOICamera:(poi_camera)poiCam
                                                 withAnimMode:(animationMode)animMode
                                                 withAnimSpeed:(NSInteger)animSpeed
                                                 followPath:(BOOL)followPath AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Remove selection model
 * @return BOOL:   YES if selection POI properly removed, NO otherwise
 */
- (BOOL)removePoiSelectionModel AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Set selection POI animation Mode
 * @param animMode   @link animationMode type
 */
- (void)setSelectionAnimationMode:(animationMode)animMode AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Set selection POI camera Mode
 * @param poiCam   @link poi_camera type
 */
- (void)setSelectionPoiCam:(poi_camera)poiCam AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Set selection POI speed
 * @param animSpeed   from fast (1) to slow (10)
 */
- (void)setSelectionPoiSpeed:(NSInteger)animSpeed AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Set whether the selection POI follows the 3D rect (path) between POIs
 * @param followPath   YES to follow the path, NO otherwise
 */
- (void)setSelectionPoiFollowPath:(BOOL)followPath AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);


/*==================================================
        3D POI ANIMATIONS
 ==================================================*/

/**
 * @brief Stop 3D POI animation
 * @param inPoi poi
 */
- (void)stopAnimation:(Poi3D*)inPoi AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief Play 3D POI animation
 * @param inPoi poi
 * @param animName animation name
 */
- (void)playAnimation:(Poi3D*)inPoi withName:(NSString*)animName AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);


/*==================================================
 MEMORY MANAGEMENT
 ==================================================*/

/**
 * @brief Release Browser
 */
- (void)releaseBrowser AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

@end
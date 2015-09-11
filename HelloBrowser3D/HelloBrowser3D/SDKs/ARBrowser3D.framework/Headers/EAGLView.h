//
//  EAGLView.h
//  EAD Framework
//
//  Copyright Aumentia. All rights reserved.
//
//

#ifndef EDR_ADVANCED
#define EDR_ADVANCED

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

/**
 * @brief Structure containing the result after loading EAD:
 * animation loaded status
 * lights loaded status
 * camera loaded status
 * objects loaded status
 * material loaded status
 * textures loaded status
 * bones loaded status
 * helpers loaded status
 */
typedef struct EAD_RESULT
{
    BOOL    IsAnimationLoaded;
    BOOL    IsLightsLoaded;
    BOOL    IsCamerasLoaded;
    BOOL    IsObjectsLoaded;
    BOOL    IsMaterialLoaded;
    BOOL    IsTexturesLoaded;
    BOOL    IsBonesLoaded;
    BOOL    IsHelpersLoaded;
    int     EADId;
}EAD_RESULT;

/**
 * @brief Camera types:
 * Trackball: rotates around the center.
 * FPS: is fixed and rotates arount itself.
 *
 */
typedef NS_ENUM(NSInteger, EAD_CAMERAS) {
    /**
     * Trackball: rotates around the center.
     */
    Trackball,
    /**
     * FPS: is fixed and rotates arount itself.
     */
    FPS,
};

/**
 *  Optional protocol
 */
@protocol renderProtocol <NSObject>

@required
/**
 *  @brief Called each rendering frame.
 *  Mandatory if the protocol is implemented.
 */
-(void)frameRendered;

@end

@class UIViewController;

/**
 * @brief The 3DR Engine Advanced SDK version is a rendering engine that includes the basic functionality to render complex objects and animations.
 * This version is thought for non 3D expert users. It is a powerful API for animation management, objects transformations, video tools,
 *  texture management, camera and lighting control.
 *
 */
__attribute__((__visibility__("default"))) @interface EAGLView : UIView<NSURLConnectionDataDelegate>
{
    UIViewController __unsafe_unretained *pMainViewController;
}


/**
 * @brief View controller where the GL view is going to be displayed.
 */
@property (nonatomic, assign) UIViewController *pMainViewController;

/**
 *  Callback delegate.
 */
@property (weak, nonatomic) id <renderProtocol> renderDelegate;


/*==================================================
 GENERAL METHODS
 ==================================================*/

/**
 * @brief Init EAGLView.
 *
 * @param frame view frame rectangle.
 * @param camera camera type.
 *
 * @return object instance.
 */
- (id)initWithFrame:(CGRect)frame withCamera:(EAD_CAMERAS)camera;

/**
 * @brief Start rendering.
 *
 */
- (void)start;

/**
 * @brief Stop rendering.
 *
 */
- (void)stop;

/**
 * @brief Release the whole world.
 *
 */
- (void)releaseWorld;

/**
 * @brief Release the GLView.
 * @discussion should be called automatically by dealloc
 *
 */
- (void)releaseGLView;

/**
 * @brief Creates a new object and generates the model id automatically.
 *
 *  @return model id within NSNumber, -1 if the model was not created.
 */
- (NSNumber*)createModel;

/**
 * @brief Creates a new object.
 *
 *  @param modelId Custom modelId. If the id is already taken the system will assign another one.
 *
 *  @return model modelId within NSNumber, -1 if the model was not created.
 */
- (NSNumber*)createModel:(NSNumber*)modelId ;

/**
 * @brief Get model modelId.
 *
 *  @param eadId Holding the model name. This name can be retrieved also using the getHierarchyNames function.
 *  @param modelName EAD id containing the object to search.
 *
 *  @return model modelId within NSNumber, -1 if the model does not exist.
 */
- (NSNumber*)getModel:(NSString*)modelName witheadId:(NSNumber*)eadId ;

/**
 * @brief Remove model from the world.
 *
 *  @param modelId Model modelId.
 *
 *  @return YES if the model has been successfully removed, NO otherwise.
 */
- (BOOL)removeModel:(NSNumber*)modelId ;

/**
 * @brief Remove all models from the world.
 *
 *  @return YES if the model has been successfully removed, NO otherwise.
 */
- (BOOL)removeAllModels;

/**
 * @brief Returns amount of models in the system
 *
 * @return Amount of models
 */
- (NSInteger)modelsCount;

/**
 * @brief Loads EAD 3D object.
 *
 *  @param path File to load from local resources.
 *
 *  @return the EAD_RESULT struct with the resulting information.
 */
- (EAD_RESULT)loadEAD:(NSString*)path;

/**
 *  @brief Loads EAD 3D object.
 *  @discussion not implemented yet.
 *
 *  @param path File to load from URL.
 *
 *  @return the EAD_RESULT struct with the resulting information.
 */
- (EAD_RESULT)loadEADfromURL:(NSString*)path ;

/**
 *  @brief Clone EAD instance.
 *  @discussion If you want to use several times the same EAD, load it once and clone it the next time.
 *
 *  @param ead_original_id Original EAD id.
 *  @param ead_cloned_sufix New EAD sufix name.
 *
 *  @return the EAD_RESULT struct with the resulting information.
 */
- (EAD_RESULT)cloneEAD:(NSNumber*)ead_original_id withSufix:(NSString*)ead_cloned_sufix;

/**
 * @brief Removes EAD resource for the EADs pool.
 *
 *  @param eadId  EAD unique ID.
 *
 *  @return YES if the EAD has been successfully removed.
 */
- (BOOL)removeEAD:(NSNumber*)eadId ;

/**
 * @brief Gives a list with the names of all objects starting from the object with given eadId.
 *
 *  @param eadId  EAD unique id.
 *
 *  @return The list of names as NSString objects.
 */
- (NSMutableArray*)getHierarchyNames:(NSNumber*)eadId ;

/**
 * @brief Gives a list with the names of all controllers starting from the object with given eadId.
 * Controllers are used to manipulate the model.
 *
 *  @param eadId  EAD unique id.
 *
 *  @return  The list of names as NSString objects.
 */
- (NSMutableArray*)getControlsNames:(NSNumber*)eadId ;

/**
 * @brief Gives a list with the names of all the meshes from the object with given eadId.
 *
 *  @param eadId  EAD unique id.
 *
 *  @return  The list of meshes as NSString objects.
 */
- (NSMutableArray*)getMeshesNames:(NSNumber*)eadId ;

/**
 *  @brief add target/action for click event to modelId object.
 *  You can call this multiple times and you can specify multiple target/actions for a particular click event.
 *
 * @param target target where you implemented the selector.
 * @param action action to perform once the event is triggered.
 * @param modelId object modelId.
 *
 * @return YES the target has been successfully added.
 */
- (BOOL)addTarget:(id)target withAction:(SEL)action withModeId:(NSNumber*)modelId ;

/**
 * @brief remove the target/action for a set of click events.
 *
 * @param target target where you implemented the selector.
 * @param modelId object modelId. Pass NULL to remove all the click events associated to the target.
 *
 * @return YES the target has been successfully removed.
 */
- (BOOL)removeTarget:(id)target withModeId:(NSNumber*)modelId ;

/**
 * @brief Attach an EAD object.
 *
 *  @param eadId EAD id.
 *  @param modelId model unique id.
 *
 *  @return YES if the EAD has been successfully attached.
 */
- (BOOL) attachEAD:(NSNumber*)eadId withModelId:(NSNumber*)modelId ;

/**
 * @brief Detach an EAD object.
 *
 *  @param eadId EAD id.
 *  @param modelId model unique id.
 *
 *  @return YES if the EAD has been successfully detached.
 */
- (BOOL) detachEAD:(NSNumber*)eadId withModelId:(NSNumber*)modelId ;

/**
 * @brief Get a list of the objects in view
 *
 *  @return Array of object ids.
 */
- (NSMutableArray*)getModelsInView;

/*==================================================
 TEXTURE METHODS
 ==================================================*/

/**
 * @brief Returns a list of textures from the object with given eadId.
 *
 *  @param modelId model unique id.
 *
 *  @return NSMutableArray with the list of textures.
 */
- (NSMutableArray*)getTexturesList:(NSNumber*)modelId ;

/**
 * @brief Replaces an existing texture with a new texture.
 *
 *  @param modelId      model unique id.
 *  @param oldTxt       The name of the existing texture.
 *  @param newTxt       Full path to the new texture.
 *  @param update       Wheter to remove old texture or keep it in memory
 *
 *  @return YES if the texture has been successfully replaced.
 */
- (BOOL)replaceTexture:(NSNumber*)modelId oldTexture:(NSString*)oldTxt newTexture:(NSString*)newTxt update:(BOOL)update;

/**
 * @brief Replaces an existing texture with a new texture.
 *
 *  @param modelId  model unique id.
 *  @param oldTxt   The name of the existing texture.
 *  @param newTxt   Full path to the new texture.
 *  @param buffer   image data
 *  @param w        image width
 *  @param h        image height
 *  @param update   wheter to remove old texture or keep it in memory
 *
 *  @return YES if the texture has been successfully replaced.
 */
- (BOOL) replaceTextureFromData:(NSNumber*)modelId oldTexture:(NSString*)oldTxt newTexture:(NSString*)newTxt newData:(NSData*)buffer witdh:(int)w height:(int)h update:(BOOL)update;

/**
 * @brief Replaces an existing texture with a new texture.
 *
 *  @param modelId  model unique id.
 *  @param oldTxt   The name of the existing texture.
 *  @param newTxt   Full path to the new texture.
 *  @param buffer   image data
 *  @param fileType image width
 *  @param fileLen  image height
 *  @param update   wheter to remove old texture or keep it in memory
 *
 *  @return YES if the texture has been successfully replaced.
 */
- (BOOL) replaceTextureFromBuffer:(NSNumber*)modelId oldTexture:(NSString*)oldTxt newTexture:(NSString*)newTxt newData:(NSData*)buffer fileType:(const char*)fileType fileLen:(size_t)fileLen update:(BOOL)update;

/**
 *  @brief Set Model Visibility.
 *
 *  @param modelId model unique id.
 *  @param visible YES to show the model, NO to hide it.
 *  @param applyToChildren YES to affect the children.
 *
 *  @return YES if successfully hidden.
 */
- (BOOL) setVisibilityForHierarhchy:(BOOL)visible applyToChildren:(BOOL)applyToChildren withModelId:(NSNumber*)modelId ;


/**
 *  @brief Set Model Alpha.
 *
 *  @param alpha_value  : alpha value
 *  @param modelId      : model Id where to apply alpha value
 *
 *  @return YES if successfully alpha applied.
 */
- (BOOL)setModelAlpha:(CGFloat)alpha_value withModelId:(NSNumber*)modelId;

/**
 *  @brief Display OpenGL Objects after load EAD in background
 *
 */
- (void)makeOpenGLObjects;

/*==================================================
 TRANSFORMATIONS METHODS
 ==================================================*/

/**
 * @brief Set Model position.
 *
 *  @param objPosition  (x,y,z) vector.
 *  @param modelId model unique id.
 *
 *  @return YES if the model position has been successfully set.
 */
- (BOOL)setModelPosition:(NSArray*)objPosition withModelId:(NSNumber*)modelId ;

/**
 * @brief Set Model scale.
 *
 *  @param objScale (x,y,z) vector.
 *  @param modelId model unique id.
 *
 *  @return YES if the model scale has been successfully set.
 */
- (BOOL)setModelScale:(NSArray*)objScale withModelId:(NSNumber*)modelId ;

/**
 *  @brief Set Model rotation.
 *
 *  @param objRot in degrees  (x,y,z) vector.
 *  @param modelId model unique id.
 *
 *  @return YES if the model rotation has been successfully set.
 */
- (BOOL)SetModelRotation:(NSArray*)objRot withModelId:(NSNumber*)modelId ;

/**
 *  @brief Set Model matrix.
 *
 *  @param objRotation 4x4 model matrix.
 *  @param modelId model unique id.
 *
 *  @return YES if the model matrix has been successfully set.
 */
- (BOOL)setModelMatrix:(NSArray*)objRotation withModelId:(NSNumber*)modelId ;

/**
 *  @brief Get Model position.
 *
 *  @param modelId model unique id.
 *
 *  @return (x,y,z) vector.
 */
- (NSArray*)getModelPosition:(NSNumber*)modelId ;

/**
 * @brief Sets the rotation offsets of the scene.
 *
 * @param vRot the rotation angles.
 * @param modelId model unique id.
 */
- (BOOL) SetRotationsOffset:(NSArray*)vRot withModelId:(NSNumber*)modelId ;

/**
 * @brief Get screen position coordinates (x,y) of modelId
 *
 * @param modelId model unique id
 *
 * @return modelId model unique id.
 */
- (CGPoint) getScreenCoords:(NSNumber*)modelId;

/**
 * @brief Get model 4x4 matrix
 *
 * @param modelId model unique id
 *
 * @return modelId model unique id.
 */
- (NSMutableArray*) getModelMatrix:(NSNumber*)modelId;

/**
 * @brief Apply rotation to model matrix
 *
 * @param modelId       model id
 * @param rotVector     rotation vector
 * @param scaleVector   scale vector
 * @param localMatrix   model id model matrix
 *
 * @return YES if rotation properly applied.
 */
- (BOOL)setRotationToModelMatrix:(NSNumber*)modelId withRotationVector:(NSArray*)rotVector withScaleVector:(NSArray*)scaleVector withOriginalLocalMatrix:(NSMutableArray*)localMatrix;

/**
 * @brief Set rotation to the engine root
 *
 * @param rotation  Model rotation
 *
 * @return YES if rotation properly applied.
 */
- (BOOL)setRootModelRotation:(NSArray*)rotation;

/**
 * @brief Set position to the engine root
 *
 * @param position Model position
 *
 * @return YES if position properly applied.
 */
- (BOOL)setRootModelPosition:(NSArray*)position;

/**
 * @brief Set scale to the engine root
 *
 * @param scale Model scale
 *
 * @return YES if scale properly applied.
 */
- (BOOL)setRootModelScale:(CGFloat)scale;

/**
 * @brief Set rotation to the root model matrix
 *
 * @param rotVector     rotation vector
 * @param localMatrix   local matrix
 *
 * @return YES if rotation properly applied.
 */
- (BOOL)setRootRotationToModelMatrix:(NSArray*)rotVector withOriginalLocalMatrix:(NSMutableArray*)localMatrix;

/**
 * @brief Get engine root model matrix
 *
 * @return Root model matrix
 */
- (NSMutableArray*) getRootModelMatrix;

/*==================================================
 ANIMATION METHODS
 ==================================================*/

/**
 * @brief Stop model animation.
 *
 * @param applyToChildren YES to apply to object children, NO otherwise.
 * @param modelId model unique id.
 *
 *  @return YES if the animation has been successfully stopped.
 */
- (BOOL) stopAnimation:(BOOL)applyToChildren withModelId:(NSNumber*)modelId ;

/**
 * @brief Pause model animation.
 *
 * @param applyToChildren YES to apply to object children, NO otherwise.
 * @param modelId model unique id.
 *
 *  @return YES if the animation has been successfully paused.
 */
- (BOOL) pauseAnimation:(BOOL)applyToChildren withModelId:(NSNumber*)modelId ;

/**
 * @brief Resume model animation.
 *
 * @param applyToChildren YES to apply to object children, NO otherwise.
 * @param modelId model unique id.
 *
 *  @return YES if the animation has been successfully resumed.
 */
- (BOOL) resumeAnimation:(BOOL)applyToChildren withModelId:(NSNumber*)modelId ;

/**
 * @brief Set animation to an object.
 *
 * @param animName animation name. Can be retrieved using getAnimationsList function.
 * @param modelId model unique id.
 *
 * @return YES if the animation has been properly set, NO otherwise.
 */
- (BOOL) setAnimation:(NSString*)animName withModelId:(NSNumber*)modelId ;

/**
 * @brief Play model animation.
 *
 * @param applyToChildren YES to apply to object children, NO otherwise.
 * @param modelId model unique id.
 *
 *  @return YES if the animation has been successfully started.
 */
- (BOOL) playAnimation:(BOOL)applyToChildren withModelId:(NSNumber*)modelId ;

/**
 * @brief Set animation speed.
 *
 *  @param applyToChildren YES to apply to object children, NO otherwise.
 *  @param speed 1.0f for normal speed.
 *				   fSpeed > 1.0f makes the animation run faster.
 *				   fSpeed < 1.0f makes the animation run slower.
 *				   fSpeed < 0.0f makes the animation run backwards.
 *  @param modelId model unique id.
 *
 *  @return YES if the animation speed has been successfully set.
 */
- (BOOL) SetAnimationSpeed:(BOOL)applyToChildren speed:(NSNumber*)speed withModelId:(NSNumber*)modelId ;

/** @brief Get the float representing the speed.
 *
 *  @param modelId model unique id.
 *
 *  @return float representation of the speed.
 */
- (NSNumber*)getAnimationSpeed:(NSNumber*)modelId ;

/**
 * @brief Set if animation loops.
 *
 * @param loop YES the animation will enter in loop mode, NO the animation will not loop once completed.
 * By default all animations starts with loop mode on.
 *  @param modelId model unique id.
 *
 *  @return YES if the animation loop has been successfully.
 */
- (BOOL)setAnimationLoop:(BOOL)loop withModelId:(NSNumber*)modelId ;

/**
 * @brief Returns a list of animations the object has.
 *
 *  @param modelId model unique id.
 *
 *  @return NSMutableArray: A list of NSString objects with the animations names.
 */
- (NSMutableArray*)getAnimationsList:(NSNumber*)modelId ;

/*==================================================
 VIDEO METHODS
 ==================================================*/

/**
 * @brief Attach a Video object. On this version, we automatically replace the video texture
 *	with the current diffuse textures. Detaching the video will remove all the diffuse textures from the model.
 *  @discussion not implemented yet.
 *
 *  @param eadId EAD unique id.
 *  @param modelId model unique id.
 *
 *  @return YES if the video has been successfully attached.
 */
- (BOOL)attachVideo:(NSNumber*)eadId withModelId:(NSNumber*)modelId ;

/**
 * @brief Detach the Video object. Detaching the video will remove all the diffuse textures from the model.
 *  @discussion not implemented yet.
 *
 *  @param modelId model unique id.
 *
 *  @return YES if the video has been successfully detached.
 */
- (BOOL)detachVideo:(NSNumber*)modelId ;

/**
 * @brief Play video.
 *  @discussion not implemented yet.
 *
 *  @param modelId model unique id.
 *
 *  @return YES if the video has been successfully started or resumed.
 */
- (BOOL)playVideo:(NSNumber*)modelId ;

/**
 * @brief Pause video.
 *  @discussion not implemented yet.
 *
 *  @param modelId model unique id.
 *
 *  @return YES if the video has been successfully paused.
 */
- (BOOL)pauseVideo:(NSNumber*)modelId ;

/**
 * @brief Stop video.
 *  @discussion not implemented yet.
 *
 *  @param modelIdM model unique id.
 *
 *  @return YES if the video has been successfully stopped.
 */
- (BOOL)stopVideo:(NSNumber*)modelIdM ;

/**
 * @brief Loads video file.
 *  @discussion not implemented yet.
 *
 *  @param path File to load from local resources.
 *
 *  @return the videoId if successfully loaded, else returns -1.
 */
- (NSNumber*)loadVideo:(NSString*)path ;

/**
 * @brief Loads video file.
 *  @discussion not implemented yet
 *
 *  @param path File to load from URL
 *
 *  @return the videoId if successfully loaded, else returns -1
 */
- (NSNumber*)loadVideoFromURL:(NSString*)path ;

/**
 * @brief Removes Video resource from the videos pool.
 *
 *  @param videoId  video unique ID.
 *
 *  @return YES if the video has been successfully removed, NO otherwise.
 */
- (BOOL)removeVideo:(NSNumber*)videoId ;

/*==================================================
 CAMERA METHODS
 ==================================================*/

/**
 * @brief Set world camera position.
 *
 *  @param camPos  (x,y,z) vector.
 *
 *  @return YES if the camera position is properly set.
 *
 */
- (BOOL) setCameraPosition:(NSArray*)camPos ;

/**
 * @brief Set camera target position.
 *
 *  @param camTarPos  (x,y,z) vector.
 *
 *  @return YES if the camera target position is properly set.
 *
 */
- (BOOL) setCameraTargetPos:(NSArray*)camTarPos ;

/**
 * @brief Set camera rotation.
 *
 *  @param rotMatrix  4x4 matrix.
 *
 *  @return YES if the camera rotation is properly set.
 *
 */
- (BOOL)setCameraRotation:(NSArray*)rotMatrix ;

/**
 * @brief Set camera type. This function can be used at run time.
 *
 * @param camera  camera time
 *
 */
- (void)setCameraActive:(EAD_CAMERAS)camera;

/**
 * @brief Set lookAt camera position
 *
 * @param  lookAtCoord  camera time
 * @param  modelId  camera time
 *
 * @return YES if the camera lookAt position is properly set.
 */
- (BOOL) lookAt:(NSArray*)lookAtCoord withModelId:(NSNumber*)modelId;


/*==================================================
 LIGHTS METHODS
 ==================================================*/

/**
 *  Sets whether the object will be affected by lights.
 *
 * @param applyToObject YES object affected by light.
 * @param applyToChildren YES to apply to object children, NO otherwise.
 * @param modelId model unique id.
 *
 * @return YES if the lights value has been successfully applied.
 */
- (BOOL) setAffectedByLights:(BOOL)applyToObject applyToChildren:(BOOL)applyToChildren withModelId:(NSNumber*)modelId ;


/*==================================================
 CLICK METHODS
 ==================================================*/

/**
 * @brief Check if a specific object is clicked.
 *
 * @param modelId object modelId.
 * @param xC X coord of the click on the screen.
 * @param yC Y coord of the click on the screen.
 *
 * @return YES if object is clicked, NO is object is not clicked.
 */
- (BOOL)isObjectClicked:(NSNumber*)modelId xClick:(NSNumber*)xC yClick:(NSNumber*)yC ;

/**
 * @brief Get clicked object list.
 *
 * @param xC X coord of the click on the screen.
 * @param yC Y coord of the click on the screen.
 *
 * @return Object clicked list.
 */
- (NSMutableArray*)getClickedObjectID:(NSNumber*)xC yClick:(NSNumber*)yC;

/**
 * @brief Get clicked object list.
 * @discussion Using RAY method. Best option for squared shapes. 
 *
 * @param xC X coord of the click on the screen.
 * @param yC Y coord of the click on the screen.
 *
 * @return Object clicked list.
 */
- (NSMutableArray*)GetClickedObjectIDByRay:(NSNumber*)xC yClick:(NSNumber*)yC;

/**
 * @brief Set an object as clickable.
 * @discussion Only objects set as clickable will be able to appear in the getClickedObjectID and GetClickedObjectIDByRay return list.
 *
 * @param activate YES set as clickable, NO remove it from clickable list.
 * @param uniqueId Unique id.
 *
 * @return YES if the object has been properly set as clickable
 */
- (BOOL)setClickListener:(NSNumber*)uniqueId activate:(BOOL)activate;

/*==================================================
 PRIVATE API
 ==================================================*/

@property (nonatomic, assign, getter = getLoadingAnimation) BOOL loadingAnimation;
@property (nonatomic, assign, getter = getUseCache) BOOL useCache;

- (void)setTexture:(NSString*)texture;
- (void)setTextureFromUrl:(NSString*)texture;
- (void)setTextureFromData: (const unsigned char*)buffer
                            textureName:(const char*) textureName
                            reload: (const bool)reload
                            bHasAlpha: (const bool) bHasAlpha
                            iWidth: (const unsigned int)  iWidth
                            iHeight: (const unsigned int) iHeight;
- (BOOL)setTextureFromBuffer: (const unsigned char*)buffer
                              fLen: (const size_t)fLen
                              fType: (const char*) fType
                              textureName: (const char*) textureName
                              reload: (const bool)reload;
- (void)setRecPoints:(float*)points originalW:(float)originalW originalH:(float)originalH;
- (void)setRecAlpha:(float)alpha;
- (void)initRectangle;

@end

#endif
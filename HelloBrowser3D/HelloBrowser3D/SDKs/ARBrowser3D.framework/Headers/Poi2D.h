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
 * File: Poi2D.h
 * Description:
 * Author: Pablo GM (info@aumentia.com)
 * Created: 23/01/15.
 * Verion 1.1
 *
 *
 **************************************************************************/

#import <Foundation/Foundation.h>
#import "Poi.h"

/**
 @brief 2D Poi. The user can set any kind of texture or event a snapshot of an UIView.
 */

__attribute__((__visibility__("default"))) @interface Poi2D : Poi
{    
    @private
        
    
        BOOL _isPoiBeingLoaded;
        
    
        BOOL _isPoiLoaded;
    
    
        BOOL _isFileSaved;
    
    
        NSURL *_url;
    
    
        NSInteger _frameLoading;
    
    
        NSString *_texturePath;
    
    
        NSString *_fileSelTexturePath;
    
    
        NSString *_fileSelNonTexturePath;
    
        CGFloat _selAlph, _nselAlph;
}

/**
 @brief isPoiBeingLoaded whether the POI is being loaded or not
 */
@property (nonatomic, assign) BOOL                  isPoiBeingLoaded;
/**
 @brief isPoiLoaded  whether the POI is loaded or not
 */
@property (nonatomic, assign) BOOL                  isPoiLoaded;
/**
 @brief isFileSaved  whether the texture has been locally stored
 */
@property (nonatomic, assign) BOOL                  isFileSaved;
/**
 @brief url  URL to download the texture to display
 */
@property (nonatomic, strong) NSURL                 *url;
/**
 @brief frameLoading  current frame being load on POI
 */
@property (nonatomic) NSInteger                     frameLoading;
/**
 @brief selAlph  Set alpha value
 */
@property (nonatomic) CGFloat                       selAlph;
/**
 @brief nselAlph  Non alpha value
 */
@property (nonatomic) CGFloat                       nselAlph;
/**
 @brief texturePath  2D POI texture
 */
@property (nonatomic, strong) NSString              *texturePath;
/**
 @brief fileSelTexturePath  path to the selection remote texture
 */
@property (nonatomic, strong) NSString              *fileSelTexturePath;
/**
 @brief fileSelNonTexturePath  path to the non selection remote texture
 */
@property (nonatomic, strong) NSString              *fileSelNonTexturePath;

/**
 * @brief set POI alpha on selection
 * @param selectedAlpha  alpha of the poi
 */
-(void)setSelectedAlpha:(CGFloat)selectedAlpha AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief get POI alpha on selection
 * @return selectedAlpha  alpha of the poi
 */
-(CGFloat)getSelectedAlpha AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief set not selected POI alpha
 * @param notSelectedAlpha  alpha of the poi
 */
-(void)setNotSelectedAlpha:(CGFloat)notSelectedAlpha AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief get not selected POI alpha
 * @return notSelectedAlpha  alpha of the poi
 */
-(CGFloat)getNotSelectedAlpha AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);


/**
 * @brief set POI texture on selection
 * @param textureSelectionPath 2D POI selection texture
 */
-(void)setTextureSelectionPath:(NSString*)textureSelectionPath AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief get POI texture on selection
 * @return textureSelectionPath 2D POI selection texture
 */
-(NSString*)getTextureSelectionPath AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief set not selected POI texture
 * @param textureNonSelectionPath 2D POI non selection texture
 */
-(void)setTextureNonSelectionPath:(NSString*)textureNonSelectionPath AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 * @brief get not selected POI texture
 * @return textureNonSelectionPath 2D POI non selection texture
 */
-(NSString*)getTextureNonSelectionPath AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 @brief set 2D POI texture from resources
 @param view UIView to set as image
 */
- (void)setTextureSelectionPathFromView:(UIView*)view AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

/**
 @brief set 2D POI texture from resources
 @param view UIView to set as image
 */
- (void)setTextureNonSelectionPathFromView:(UIView*)view AR3DBrowser_AVAILABLE(AR3DBrowser_V_0_1_1);

@end
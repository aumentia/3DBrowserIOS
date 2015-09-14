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
 * File: PoiRadarController.h
 * Description:
 * Author: Pablo GM (info@aumentia.com)
 * Created: 23/01/15.
 * Verion 1.1
 *
 *
 **************************************************************************/

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <ARBrowser3D/Poi.h>
#import "_radar_1_versions.h"

__attribute__((__visibility__("default"))) @interface PoiRadarController : UIViewController
{
    UIImage*            _radarImage;
    UIImage*            _poiImage;
    UIImage*            _poiImageSelected;
    UIImage*            _northImage; 
    NSMutableArray*     _poisArray;
    CLLocation*         _userLocation;
    Poi*                _selectedPoi;
   
}

/**
 * Radar image
 */
@property (strong, nonatomic) UIImage           *radarImage;
/**
 * POI image
 */
@property (strong, nonatomic) UIImage           *poiImage;
/**
 * POI selected image
 */
@property (strong, nonatomic) UIImage           *poiImageSelected;
/**
 * North image
 */
@property (strong, nonatomic) UIImage           *northImage;
/**
 * Array of all POIs
 */
@property (strong, nonatomic) NSMutableArray    *poisArray;
/**
 * User location
 */
@property (strong, nonatomic) CLLocation        *userLocation;
/**
 * Selected POI
 */
@property (strong, nonatomic) Poi               *selectedPoi;

/**
 * @brief Init the radar
 *
 * @param key  license key
 */
- (id)initWithKey:(NSString *)key _radar_1_AVAILABLE(_radar_1_V_0_1_1);

/**
 * @brief Refresh the radar
 */
- (void)refresh _radar_1_AVAILABLE(_radar_1_V_0_1_1);

/**
 * @brief Delete the POIs and reinsert them
 */
- (void)reset _radar_1_AVAILABLE(_radar_1_V_0_1_1);

/**
 * @brief Rotate radar view
 *
 * @param degrees the angle to rotate the radar in degrees
 */
- (void)rotateRadarView:(double)degrees _radar_1_AVAILABLE(_radar_1_V_0_1_1);

/**
 * @brief Set CLHeading instance
 *
 * @param newHeading heading instance
 */
- (void)setHeading:(CLHeading*)newHeading _radar_1_AVAILABLE(_radar_1_V_0_1_1);

/**
 * @brief Set CLLocation instance
 *
 * @param userLocation location instance
 */
- (void)setUserLocation:(CLLocation *)userLocation _radar_1_AVAILABLE(_radar_1_V_0_1_1);

@end
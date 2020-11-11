/**
 ****************************************************************************************
 *
 * @file user_profiles_config.h
 *
 * @brief Configuration file for the profiles used in the application.
 *
 * Copyright (C) 2017-2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef _USER_PROFILES_CONFIG_H_
#define _USER_PROFILES_CONFIG_H_

/**
 ****************************************************************************************
 * @defgroup APP_CONFIG
 * @ingroup APP
 * @brief  Application configuration file
 *
 * This file contains the configuration of the profiles used by the application.
 *
 * @{
 ****************************************************************************************
 */

/*
 * DEFINITIONS
 ****************************************************************************************
 */
#define FRAME_SIDE_NAME 0 //1 = Left, 0 = Right

/***************************************************************************************/
/* Used BLE profiles (used by "rwprf_config.h").                                       */
/***************************************************************************************/

#define CFG_PRF_DISS
#define CFG_PRF_CUST1

/***************************************************************************************/
/* Profile application configuration section                                           */
/***************************************************************************************/

/*
 ****************************************************************************************
 * DISS application profile configuration
 ****************************************************************************************
 */

#define APP_DIS_FEATURES                (DIS_MANUFACTURER_NAME_CHAR_SUP | \
                                        DIS_MODEL_NB_STR_CHAR_SUP)

/// Manufacturer Name
#define APP_DIS_MANUFACTURER_NAME       ("SMARCH")
#define APP_DIS_MANUFACTURER_NAME_LEN   (6)

/// Model Number String
#if defined (__DA14586__)
    #define APP_DIS_MODEL_NB_STR            ("DA14586")
#elif defined (__DA14531__)
		#if FRAME_SIDE_NAME
    #define APP_DIS_MODEL_NB_STR            ("GLASSES_LEFT")
		#define APP_DIS_MODEL_NB_STR_LEN        (12)
		#else
    #define APP_DIS_MODEL_NB_STR            ("GLASSES_RIGHT")
		#define APP_DIS_MODEL_NB_STR_LEN        (13)
		#endif
#else
     #define APP_DIS_MODEL_NB_STR           ("DA14585")
#endif
//#define APP_DIS_MODEL_NB_STR_LEN        (7)

/// System ID - LSB -> MSB
#define APP_DIS_SYSTEM_ID               ("\x12\x34\x56\xFF\xFE\x9A\xBC\xDE")
#define APP_DIS_SYSTEM_ID_LEN           (8)

#define APP_DIS_SW_REV                  SDK_VERSION
#define APP_DIS_FIRM_REV                SDK_VERSION

/// Serial Number
#define APP_DIS_SERIAL_NB_STR           ("1.0.0.0-LE")
#define APP_DIS_SERIAL_NB_STR_LEN       (10)

/// Hardware Revision String
#if defined (__DA14586__)
    #define APP_DIS_HARD_REV_STR            ("DA14586")
#elif defined (__DA14531__)
    #define APP_DIS_HARD_REV_STR            ("DA14531")
#else
    #define APP_DIS_HARD_REV_STR            ("DA14585")
#endif
#define APP_DIS_HARD_REV_STR_LEN        (7)

/// Firmware Revision
#define APP_DIS_FIRM_REV_STR            SDK_VERSION
#define APP_DIS_FIRM_REV_STR_LEN        (sizeof(APP_DIS_FIRM_REV_STR) - 1)

/// Software Revision String
#define APP_DIS_SW_REV_STR              SDK_VERSION
#define APP_DIS_SW_REV_STR_LEN          (sizeof(APP_DIS_SW_REV_STR) - 1)

/// IEEE
#define APP_DIS_IEEE                    ("\xFF\xEE\xDD\xCC\xBB\xAA")
#define APP_DIS_IEEE_LEN                (6)

/**
 * PNP ID Value - LSB -> MSB
 *      Vendor ID Source : 0x02 (USB Implementers Forum assigned Vendor ID value)
 *      Vendor ID : 0x045E      (Microsoft Corp)
 *      Product ID : 0x0040
 *      Product Version : 0x0300
 * e.g. #define APP_DIS_PNP_ID          ("\x02\x5E\x04\x40\x00\x00\x03")
 */
#define APP_DIS_PNP_ID                  ("\x01\xD2\x00\x80\x05\x00\x01")
#define APP_DIS_PNP_ID_LEN              (7)

/*
 ****************************************************************************************
 * CUST1 application profile configuration
 ****************************************************************************************
 */

/// @} APP_CONFIG

#endif // _USER_PROFILES_CONFIG_H_

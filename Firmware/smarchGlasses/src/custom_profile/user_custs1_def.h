/**
 ****************************************************************************************
 *
 * @file user_custs1_def.h
 *
 * @brief Custom Server 1 (CUSTS1) profile database definitions.
 *
 * Copyright (C) 2016-2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef _USER_CUSTS1_DEF_H_
#define _USER_CUSTS1_DEF_H_

/**
 ****************************************************************************************
 * @defgroup USER_CONFIG
 * @ingroup USER
 * @brief Custom Server 1 (CUSTS1) profile database definitions.
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "attm_db_128.h"

/*
 * DEFINES
 ****************************************************************************************
 */

// Service 1 of the custom server 1
#define DEF_SVC1_UUID_128                {0x59, 0x5a, 0x08, 0xe4, 0x86, 0x2a, 0x9e, 0x8f, 0xe9, 0x11, 0xbc, 0x7c, 0x98, 0x43, 0x42, 0x18}

#define DEF_SVC1_LED_STATE_UUID_128      {0x4F, 0x43, 0x31, 0x3C, 0x93, 0x92, 0x42, 0xE6, 0xA8, 0x76, 0xFA, 0x3B, 0xEF, 0xB4, 0x87, 0x5A}

#define DEF_SVC1_LED_STATE_CHAR_LEN      1

#define DEF_SVC1_LED_STATE_USER_DESC     "LED State Color (0=Off, 1=R, 2=G, 3=B, 4=W)"

//ADDED
#define DEF_SVC1_LED_TIME_UUID_128			 {0xCD, 0x9D, 0x58, 0x15, 0x22, 0x19, 0xFE, 0x9A, 0xC5, 0x4C, 0x47, 0xCE, 0x78, 0x0E, 0xF8, 0xBB}
//{bbf80e78-ce47-4cc5-9afe-192215589dcd}
#define DEF_SVC1_LED_TIME_CHAR_LEN			 1

#define DEF_SVC1_LED_TIME_USER_DESC			 "LED On Time (100x ms)"

/// Custom1 Service Data Base Characteristic enum
enum
{
    // Custom Service 1
    SVC1_IDX_SVC = 0,

    SVC1_IDX_LED_STATE_CHAR,
    SVC1_IDX_LED_STATE_VAL,
    SVC1_IDX_LED_STATE_USER_DESC,
		//ADDED
		SVC1_IDX_LED_TIME_CHAR,
		SVC1_IDX_LED_TIME_VAL,
		SVC1_IDX_LED_TIME_USER_DESC,

    CUSTS1_IDX_NB
};

/// @} USER_CONFIG

#endif // _USER_CUSTS1_DEF_H_

/**
 ****************************************************************************************
 *
 * @file user_custs1_impl.c
 *
 * @brief Peripheral project Custom1 Server implementation source code.
 *
 * Copyright (C) 2015-2019 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "gpio.h"
#include "app_api.h"
#include "app.h"
#include "prf_utils.h"
#include "custs1.h"
#include "custs1_task.h"
#include "user_custs1_def.h"
#include "user_custs1_impl.h"
#include "user_peripheral.h"
#include "user_periph_setup.h"
#include "user_io_expander_driver.h"


/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

ke_msg_id_t timer_used      __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY
uint16_t indication_counter __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY
uint16_t non_db_val_counter __SECTION_ZERO("retention_mem_area0"); //@RETENTION MEMORY
bool notificationState			__SECTION_ZERO("retention_mem_area0"); // @RETENTION MEMORY
uint16_t ledOnTime					__SECTION_ZERO("retention_mem_area0"); // @RETENTION MEMORY

static void timer_cb(void);
static timer_hnd timer_id __attribute__((section("retention_mem_area0"),zero_init));

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */
void user_svc1_led_time_wr_ind_handler(ke_msg_id_t const msgid,
                                     struct custs1_val_write_ind const *param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id)
{
    uint8_t val = 0;
    memcpy(&val, &param->value[0], param->length);
		ledOnTime = (val*10);
}

void user_svc1_led_wr_ind_handler(ke_msg_id_t const msgid,
                                     struct custs1_val_write_ind const *param,
                                     ke_task_id_t const dest_id,
                                     ke_task_id_t const src_id)
{
    uint8_t val = 0;
    memcpy(&val, &param->value[0], param->length);
	
#if (USING_DEV_KIT)
    if (val == CUSTS1_LED_ON)
    {
				notificationState = true;
        GPIO_SetActive(GPIO_LED_PORT, GPIO_LED_PIN);
				timer_id = app_easy_timer(ledOnTime, timer_cb);
    }
    else if (val == CUSTS1_LED_OFF)
    {
				notificationState = false;
        GPIO_SetInactive(GPIO_LED_PORT, GPIO_LED_PIN);
				timer_id = app_easy_timer(ledOnTime, timer_cb);
    }	
#else
		switch(val)
		{
			//Off
			case 0:
				notificationState = false;
				i2c_ioExpander_AllLow();
				break;
			//Red
			case 1:
				notificationState = true;
				i2c_ioExpander_RedHigh();
				timer_id = app_easy_timer(ledOnTime, timer_cb);
				break;
			//Green
			case 2:
				notificationState = true;
				i2c_ioExpander_GreenHigh();
				timer_id = app_easy_timer(ledOnTime, timer_cb);
				break;
			//Blue
			case 3:
				notificationState = true;
				i2c_ioExpander_BlueHigh();
				timer_id = app_easy_timer(ledOnTime, timer_cb);
				break;
			//White
			case 4:
				notificationState = true;
				i2c_ioExpander_AllHigh();
				timer_id = app_easy_timer(ledOnTime, timer_cb);
				break;
			//Off
			default:
				notificationState = false;
				i2c_ioExpander_AllLow();
				break;
		}
#endif
}
static void timer_cb(void)
{
#if (USING_DEV_KIT)
				notificationState = false;
        GPIO_SetInactive(GPIO_LED_PORT, GPIO_LED_PIN);
#else
				notificationState = false;
				i2c_ioExpander_AllLow();
#endif
}

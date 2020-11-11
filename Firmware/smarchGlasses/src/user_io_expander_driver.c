/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "compiler.h"
#include "ll.h"
#include "user_io_expander_driver.h"
#include "i2c.h"


uint8_t currentIOExpanderState;

 /**
 ****************************************************************************************
 * @brief Initialize I2C IO Expander
 ****************************************************************************************
 */
void i2c_ioExpander_initialize(void)
{
	currentIOExpanderState = 0x00;
	i2c_ioExpander_AllLow();
}
 /**
 ****************************************************************************************
 * @brief Set I2C IO Expander Pin High
 * @param[in] ioExpander_pinNumber    Pin number to set
 * @param[in] ioExpander_HiLo   Whether to set the pin high or low
 ****************************************************************************************
 */
 void i2c_ioExpander_pinSet(uint8_t ioExpander_pinNumber, uint8_t ioExpander_HiLo)
 {
	i2c_abort_t abrt_code;
	if(ioExpander_HiLo)
	{
		currentIOExpanderState |= 1 << ioExpander_pinNumber;
	}
	else
	{
		currentIOExpanderState &= ~(1 << ioExpander_pinNumber);
	}
	//Disable controller to change slave address 
	i2c_set_controller_status(I2C_CONTROLLER_DISABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_DISABLE));
	i2c_set_target_address(IOEXPANDER_ADDRESS);
	i2c_set_controller_status(I2C_CONTROLLER_ENABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_ENABLE));
	i2c_master_transmit_buffer_sync(&currentIOExpanderState,sizeof(currentIOExpanderState),&abrt_code,I2C_F_NONE);
 }
 
 /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_AllHigh(void)
 {
	currentIOExpanderState = 0x0F;
	i2c_abort_t abrt_code;
	//Disable controller to change slave address 
	i2c_set_controller_status(I2C_CONTROLLER_DISABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_DISABLE));
	i2c_set_target_address(IOEXPANDER_ADDRESS);
	i2c_set_controller_status(I2C_CONTROLLER_ENABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_ENABLE));
	i2c_master_transmit_buffer_sync(&currentIOExpanderState,sizeof(currentIOExpanderState),&abrt_code,I2C_F_NONE);
 }
 
  /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_RedHigh(void)
 {
	currentIOExpanderState = 0x01;
	i2c_abort_t abrt_code;
	//Disable controller to change slave address 
	i2c_set_controller_status(I2C_CONTROLLER_DISABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_DISABLE));
	i2c_set_target_address(IOEXPANDER_ADDRESS);
	i2c_set_controller_status(I2C_CONTROLLER_ENABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_ENABLE));
	i2c_master_transmit_buffer_sync(&currentIOExpanderState,sizeof(currentIOExpanderState),&abrt_code,I2C_F_NONE);
 }
 
  /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_GreenHigh(void)
 {
	currentIOExpanderState = 0x02;
	i2c_abort_t abrt_code;
	//Disable controller to change slave address 
	i2c_set_controller_status(I2C_CONTROLLER_DISABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_DISABLE));
	i2c_set_target_address(IOEXPANDER_ADDRESS);
	i2c_set_controller_status(I2C_CONTROLLER_ENABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_ENABLE));
	i2c_master_transmit_buffer_sync(&currentIOExpanderState,sizeof(currentIOExpanderState),&abrt_code,I2C_F_NONE);
 }
 
  /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_BlueHigh(void)
 {
	currentIOExpanderState = 0x04;
	i2c_abort_t abrt_code;
	//Disable controller to change slave address 
	i2c_set_controller_status(I2C_CONTROLLER_DISABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_DISABLE));
	i2c_set_target_address(IOEXPANDER_ADDRESS);
	i2c_set_controller_status(I2C_CONTROLLER_ENABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_ENABLE));
	i2c_master_transmit_buffer_sync(&currentIOExpanderState,sizeof(currentIOExpanderState),&abrt_code,I2C_F_NONE);
 }
 
 
 /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All Low
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_AllLow(void)
 {
	currentIOExpanderState = 0x00;
	i2c_abort_t abrt_code;
	//Disable controller to change slave address 
	i2c_set_controller_status(I2C_CONTROLLER_DISABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_DISABLE));
	i2c_set_target_address(IOEXPANDER_ADDRESS);
	i2c_set_controller_status(I2C_CONTROLLER_ENABLE);
	while ((i2c_get_controller_status() != I2C_CONTROLLER_ENABLE));
	i2c_master_transmit_buffer_sync(&currentIOExpanderState,sizeof(currentIOExpanderState),&abrt_code,I2C_F_NONE);
 }

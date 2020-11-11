#ifndef _I2C_IOEXPANDER_H_
#define _I2C_IOEXPANDER_H_
/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"
/*
 * DEFINES
 ****************************************************************************************
 */ 
 #define IOEXPANDER_ADDRESS 0x24
 
/// Expander Pin Number
typedef enum
{
    I2C_IOEXPANDER_P0 = 0,
    I2C_IOEXPANDER_P1 = 1,
    I2C_IOEXPANDER_P2 = 2,
    I2C_IOEXPANDER_P3 = 3,
} i2c_ioExpander_portPins;

/// Expander High Low
typedef enum
{
    I2C_IOEXPANDER_LOW = 0,
    I2C_IOEXPANDER_HIGH = 1,
} i2c_ioExpander_HiLo;

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

 /**
 ****************************************************************************************
 * @brief Initialize I2C IO Expander
 ****************************************************************************************
 */
void i2c_ioExpander_initialize(void);


 /**
 ****************************************************************************************
 * @brief Set I2C IO Expander Pin High
 * @param[in] ioExpander_pinNumber    Pin number to set
 * @param[in] ioExpander_HiLo   Whether to set the pin high or low
 ****************************************************************************************
 */
 void i2c_ioExpander_pinSet(uint8_t ioExpander_pinNumber, uint8_t ioExpander_HiLo);
 
 /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_AllHigh(void);
 
  /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_RedHigh(void);
 
  /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_GreenHigh(void);
 
  /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All High
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_BlueHigh(void);
 
 
 /**
 ****************************************************************************************
 * @brief Set I2C IO Expander All Low
 * @param[in] ioExpander_pin    Pin number to set
 ****************************************************************************************
 */
 void i2c_ioExpander_AllLow(void);
 #endif // _I2C_IOEXPANDER_H_

///@}
///@}

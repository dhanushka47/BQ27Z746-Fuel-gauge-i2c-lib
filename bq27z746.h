#ifndef BQ27Z746_H
#define BQ27Z746_H

#include <stdint.h>
#include <stdbool.h>
#include <ti/display/Display.h>
#include <ti/drivers/I2C.h>

// I2C Address of the BQ27Z746
#define BQ27Z746_I2C_ADDRESS 0x55

// Register Command Definitions
#define BQ27Z746_CMD_VOLTAGE                   0x08
#define BQ27Z746_CMD_TEMPERATURE               0x06
#define BQ27Z746_CMD_CURRENT                   0x0A
#define BQ27Z746_CMD_RELATIVE_STATE_OF_CHARGE  0x0D
#define BQ27Z746_CMD_FULL_CHARGE_CAPACITY      0x10
#define BQ27Z746_CMD_REMAINING_CAPACITY        0x0F
#define BQ27Z746_CMD_TIME_TO_EMPTY             0x11
#define BQ27Z746_CMD_TIME_TO_FULL              0x13
#define BQ27Z746_CMD_CYCLE_COUNT               0x17
#define BQ27Z746_CMD_STATE_OF_HEALTH           0x4F
#define BQ27Z746_CMD_DESIGN_CAPACITY           0x18
#define BQ27Z746_CMD_DESIGN_ENERGY             0x19

// Feature Configuration Registers
#define BQ27Z746_OP_STATUS                     0x54
#define BQ27Z746_OP_CONFIG_A                   0x41
#define BQ27Z746_OP_CONFIG_B                   0x42
#define BQ27Z746_PROTECTION_CONFIG             0x57
#define BQ27Z746_CHARGE_TERM_CONFIG            0x5B
#define BQ27Z746_FET_CONTROL_REGISTER          0x56

// Function Prototypes
bool BQ27Z746_Init(I2C_Handle i2c);
bool BQ27Z746_ReadRegister(uint8_t reg, uint8_t *data, uint8_t len);
bool BQ27Z746_WriteRegister(uint8_t reg, uint8_t *data, uint8_t len);

// Feature Enable Functions
bool BQ27Z746_EnableGauge(void);
bool BQ27Z746_EnableSleepMode(void);
bool BQ27Z746_EnableGPOUT(void);
bool BQ27Z746_EnableChargeTermination(void);
bool BQ27Z746_EnableProtections(void);
bool BQ27Z746_EnableFET(void);


// Data Retrieval Functions
uint16_t BQ27Z746_GetVoltage(void);
uint16_t BQ27Z746_GetTemperature(void);
uint16_t BQ27Z746_GetCurrent(void);
uint8_t BQ27Z746_GetRelativeStateOfCharge(void);
uint16_t BQ27Z746_GetFullChargeCapacity(void);
uint16_t BQ27Z746_GetRemainingCapacity(void);
uint16_t BQ27Z746_GetTimeToEmpty(void);
uint16_t BQ27Z746_GetTimeToFull(void);
uint16_t BQ27Z746_GetCycleCount(void);
uint8_t  BQ27Z746_GetStateOfHealth(void);
uint16_t BQ27Z746_GetDesignCapacity(void);
uint16_t BQ27Z746_GetDesignEnergy(void);

// Feature Confirmation
void BQ27Z746_ConfirmEnabledFeatures(Display_Handle display);
// Function to check if the FET is enabled
bool BQ27Z746_IsFETEnabled(Display_Handle display);


#endif // BQ27Z746_H

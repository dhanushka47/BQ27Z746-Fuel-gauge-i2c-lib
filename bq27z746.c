#include "bq27z746.h"
#include <ti/display/Display.h>
#include <ti/drivers/I2C.h>
#include "ti_drivers_config.h"

// Static variable to store the I2C handle
static I2C_Handle bq27z746_i2cHandle;

// I2C initialization
bool BQ27Z746_Init(I2C_Handle i2c) {
    if (i2c == NULL) {
        return false; // Ensure a valid I2C handle is passed
    }
    bq27z746_i2cHandle = i2c; // Store the handle for future transactions
    return true;
}

// Generic function to read from a register
bool BQ27Z746_ReadRegister(uint8_t reg, uint8_t *data, uint8_t len) {
    if (bq27z746_i2cHandle == NULL) {
        return false; // Ensure the handle is initialized
    }

    I2C_Transaction i2cTransaction;
    i2cTransaction.slaveAddress = BQ27Z746_I2C_ADDRESS;
    i2cTransaction.writeBuf = &reg;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = data;
    i2cTransaction.readCount = len;

    return I2C_transfer(bq27z746_i2cHandle, &i2cTransaction);
}

// Generic function to write to a register
bool BQ27Z746_WriteRegister(uint8_t reg, uint8_t *data, uint8_t len) {
    if (bq27z746_i2cHandle == NULL) {
        return false; // Ensure the handle is initialized
    }

    uint8_t buffer[len + 1];
    buffer[0] = reg;
    for (uint8_t i = 0; i < len; i++) {
        buffer[i + 1] = data[i];
    }

    I2C_Transaction i2cTransaction;
    i2cTransaction.slaveAddress = BQ27Z746_I2C_ADDRESS;
    i2cTransaction.writeBuf = buffer;
    i2cTransaction.writeCount = len + 1;
    i2cTransaction.readBuf = NULL;
    i2cTransaction.readCount = 0;

    return I2C_transfer(bq27z746_i2cHandle, &i2cTransaction);
}

// Feature Enable Functions
bool BQ27Z746_EnableGauge(void) {
    uint8_t data[2] = {0x10, 0x00}; // Bit 4 set to enable Gauge
    return BQ27Z746_WriteRegister(0x54, data, 2);
}

bool BQ27Z746_EnableSleepMode(void) {
    uint8_t data[1] = {0x02}; // Bit 1 set to enable Sleep Mode
    return BQ27Z746_WriteRegister(0x42, data, 1);
}

bool BQ27Z746_EnableGPOUT(void) {
    uint8_t data[1] = {0x01}; // Bit 0 set to enable GPOUT
    return BQ27Z746_WriteRegister(0x41, data, 1);
}

bool BQ27Z746_EnableChargeTermination(void) {
    uint8_t data[1] = {0x01}; // Bit 0 set to enable Charge Termination
    return BQ27Z746_WriteRegister(0x5B, data, 1);
}

bool BQ27Z746_EnableProtections(void) {
    uint8_t data[1] = {0xFF}; // Enable all protections
    return BQ27Z746_WriteRegister(0x57, data, 1);
}

bool BQ27Z746_EnableFET(void) {
    uint8_t data[1] = {0x01}; // Set the appropriate bit for enabling FET
    return BQ27Z746_WriteRegister(0x56, data, 1);
}


//###################################################################
// Data Retrieval Functions
// Specific functions for each register
uint16_t BQ27Z746_GetVoltage(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_VOLTAGE, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetTemperature(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_TEMPERATURE, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetCurrent(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_CURRENT, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint8_t BQ27Z746_GetRelativeStateOfCharge(void) {
    uint8_t data[1];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_RELATIVE_STATE_OF_CHARGE, data, 1)) {
        return data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetFullChargeCapacity(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_FULL_CHARGE_CAPACITY, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetRemainingCapacity(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_REMAINING_CAPACITY, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetTimeToEmpty(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_TIME_TO_EMPTY, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetTimeToFull(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_TIME_TO_FULL, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetCycleCount(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_CYCLE_COUNT, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint8_t BQ27Z746_GetStateOfHealth(void) {
    uint8_t data[1];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_STATE_OF_HEALTH, data, 1)) {
        return data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetDesignCapacity(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_DESIGN_CAPACITY, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

uint16_t BQ27Z746_GetDesignEnergy(void) {
    uint8_t data[2];
    if (BQ27Z746_ReadRegister(BQ27Z746_CMD_DESIGN_ENERGY, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0; // Error
}

//############################################################################
// Function to confirm the status of enabled features
void BQ27Z746_ConfirmEnabledFeatures(Display_Handle display) {
    uint8_t data;

    // Confirm Fuel Gauge Enable
    if (BQ27Z746_ReadRegister(0x54, &data, 1) && (data & 0x10)) {
        Display_printf(display, 0, 0, "Fuel Gauge is Enabled.\n");
    } else {
        Display_printf(display, 0, 0, "Fuel Gauge is NOT Enabled.\n");
    }

    // Confirm Sleep Mode Enable
    if (BQ27Z746_ReadRegister(0x42, &data, 1) && (data & 0x02)) {
        Display_printf(display, 0, 0, "Sleep Mode is Enabled.\n");
    } else {
        Display_printf(display, 0, 0, "Sleep Mode is NOT Enabled.\n");
    }

    // Confirm GPOUT Enable
    if (BQ27Z746_ReadRegister(0x41, &data, 1) && (data & 0x01)) {
        Display_printf(display, 0, 0, "GPOUT is Enabled.\n");
    } else {
        Display_printf(display, 0, 0, "GPOUT is NOT Enabled.\n");
    }

    // Confirm Protections Enable
    if (BQ27Z746_ReadRegister(0x57, &data, 1) && (data == 0xFF)) {
        Display_printf(display, 0, 0, "Protections are Enabled.\n");
    } else {
        Display_printf(display, 0, 0, "Protections are NOT Enabled.\n");
    }

    // Confirm FET Enable
    if (BQ27Z746_ReadRegister(0x56, &data, 1) && (data & 0x01)) {
        Display_printf(display, 0, 0, "FET is Enabled.\n");
    } else {
        Display_printf(display, 0, 0, "FET is NOT Enabled.\n");
    }
}



// Function to check if the FET is enabled
bool BQ27Z746_IsFETEnabled(Display_Handle display) {
    uint8_t data[1];
    if (BQ27Z746_ReadRegister(BQ27Z746_FET_CONTROL_REGISTER, data, 1)) {
        if (data[0] & 0x01) { // Example: Bit 0 indicates FET status
            Display_printf(display, 0, 0, "FET is Enabled.\n");
            return true;
        } else {
            Display_printf(display, 0, 0, "FET is NOT Enabled.\n");
            return false;
        }
    }
    Display_printf(display, 0, 0, "Failed to read FET status.\n");
    return false;
}


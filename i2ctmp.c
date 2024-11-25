#include "bq27z746.h"
#include <ti/drivers/I2C.h>
#include <ti/display/Display.h>
#include "ti_drivers_config.h"

void *mainThread(void *arg0) {
    I2C_Handle i2c;
    I2C_Params i2cParams;
    Display_Handle display;

    /* Initialize drivers */
    I2C_init();
    Display_init();

    /* Open UART display for output */
    display = Display_open(Display_Type_UART, NULL);
    if (display == NULL) {
        while (1); // Halt if display fails to initialize
    }

    Display_printf(display, 0, 0, "Initializing BQ27Z746...\n");

    /* Configure I2C parameters */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;
    i2c = I2C_open(CONFIG_I2C_TMP, &i2cParams);

    if (i2c == NULL) {
        Display_printf(display, 0, 0, "I2C initialization failed.\n");
        return NULL;
    }

    /* Initialize BQ27Z746 */
    if (!BQ27Z746_Init(i2c)) {
        Display_printf(display, 0, 0, "BQ27Z746 initialization failed.\n");
        I2C_close(i2c);
        return NULL;
    }

    /* Enable FET */
       Display_printf(display, 0, 0, "Enabling FET...\n");
       if (BQ27Z746_EnableFET()) {
           Display_printf(display, 0, 0, "FET Enable Command Sent.\n");
       } else {
           Display_printf(display, 0, 0, "Failed to Enable FET.\n");
       }

       /* Confirm FET Status */
       BQ27Z746_IsFETEnabled(display);

    /* Confirm Enabled Features */
    BQ27Z746_ConfirmEnabledFeatures(display);

    /* Retrieve and Display Data */
     Display_printf(display, 0, 0, "Voltage: %u mV\n", BQ27Z746_GetVoltage());
     Display_printf(display, 0, 0, "Temperature: %u\n", BQ27Z746_GetTemperature());
     Display_printf(display, 0, 0, "Current: %u mA\n", BQ27Z746_GetCurrent());
     Display_printf(display, 0, 0, "Relative State of Charge: %u%%\n", BQ27Z746_GetRelativeStateOfCharge());
     Display_printf(display, 0, 0, "Full Charge Capacity: %u mAh\n", BQ27Z746_GetFullChargeCapacity());
     Display_printf(display, 0, 0, "Remaining Capacity: %u mAh\n", BQ27Z746_GetRemainingCapacity());
     Display_printf(display, 0, 0, "Time to Empty: %u minutes\n", BQ27Z746_GetTimeToEmpty());
     Display_printf(display, 0, 0, "Time to Full: %u minutes\n", BQ27Z746_GetTimeToFull());
     Display_printf(display, 0, 0, "Cycle Count: %u\n", BQ27Z746_GetCycleCount());
     Display_printf(display, 0, 0, "State of Health: %u%%\n", BQ27Z746_GetStateOfHealth());
     Display_printf(display, 0, 0, "Design Capacity: %u mAh\n", BQ27Z746_GetDesignCapacity());
     Display_printf(display, 0, 0, "Design Energy: %u mWh\n", BQ27Z746_GetDesignEnergy());


    /* Close I2C */
    I2C_close(i2c);
    Display_printf(display, 0, 0, "I2C Closed. Test Complete.\n");

    return NULL;
}

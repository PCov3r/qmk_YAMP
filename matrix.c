#include "quantum.h"
#include "matrix.h"
#include "print.h"
#include "seesaw.h"
#include "neotrellis.h"
#include "neopixel.h"
#include "rgb_driver.h"


// QMK required function: Initialize the matrix pins
void matrix_init_custom(void) {
    exchange_led_index(&g_led_config, ORIENTATION);
    exchange_led_positions(&g_led_config, ORIENTATION);
    // Set row pins as outputs
    i2c_init();
    Seesaw_resetAllRegisters();
    Seesaw_enableKeypadInterrupt();
    i2c_status_t status = i2c_ping_address(MY_I2C_ADDRESS, 100);
    uprintf("i2c device status: %d",status);
    for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
        Seesaw_activateKey(i, SEESAW_KEYPAD_EDGE_RISING, true);
        Seesaw_activateKey(i, SEESAW_KEYPAD_EDGE_FALLING, true);
    }    
    rgb_matrix_driver_init();
}

// QMK required function: Scan the matrix
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = Seesaw_readTrellis(true, current_matrix);
    return changed;
}


#include "quantum.h"
#include "matrix.h"
#include "print.h"
#include "seesaw.h"
#include "neotrellis.h"
#include "neopixel.h"
#include "rgb_driver.h"

// QMK required function: Initialize the matrix pins
void matrix_init_custom(void) {
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
    // for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    //     rgb_matrix_driver_set_color(i, 255, 0, 0); // red
    // }
    // rgb_matrix_driver_flush();
}

// QMK required function: Scan the matrix
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    static const trellis_orientation_t orientation = ORIENT_180;
    bool changed = Seesaw_readTrellis(true, current_matrix, orientation);
    return changed;
}


#include "quantum.h"
#include "matrix.h"
#include "print.h"
#include "seesaw.h"

// QMK required function: Initialize the matrix pins
void matrix_init_custom(void) {
    // Set row pins as outputs
    i2c_init();
    
}

// QMK required function: Scan the matrix
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    i2c_status_t status = i2c_ping_address(MY_I2C_ADDRESS, 100);
    uprintf("%d",status);
    return false;
}

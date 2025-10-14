#include "quantum.h"
#include "matrix.h"
#include "print.h"
#include "seesaw.h"

void SeeSaw_Init(void);
void resetAllRegisters(void);
bool SeeSaw_Write(uint8_t regHigh, uint8_t regLow, const uint8_t *buf, uint8_t num);

// QMK required function: Initialize the matrix pins
void matrix_init_custom(void) {
    // Set row pins as outputs
    SeeSaw_Init();
    
    
}

// QMK required function: Scan the matrix
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    i2c_status_t status = i2c_ping_address(MY_I2C_ADDRESS, 100);
    uprintf("%d",status);
    return false;
}


void SeeSaw_Init(void)
{

    i2c_init();
    resetAllRegisters();
}

void resetAllRegisters(void)
{
    uint8_t val = STATUS_RESET_REG;
    SeeSaw_Write(STATUS_BASE_REG, STATUS_SWRST_REG, &val, 1);
}

bool SeeSaw_Write(uint8_t regHigh, uint8_t regLow, const uint8_t *buf, uint8_t num)
{
    uint8_t data[2 + num];

    data[0] = regHigh;
    data[1] = regLow;

    // Copy payload if provided
    if (buf != NULL && num > 0)
    {
        memcpy(&data[2], buf, num);
    }

    if (!i2c_transmit(MY_I2C_ADDRESS, data, 2 + num, 50))
    {
        return false;
    }

    return true;

}
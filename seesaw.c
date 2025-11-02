#include "seesaw.h"

void Seesaw_resetAllRegisters(void)
{
    uint8_t val = STATUS_RESET_REG;
    SeeSaw_Write(STATUS_BASE_REG, STATUS_SWRST_REG, &val, 1);
    wait_ms(500);
}

bool SeeSaw_Write(uint8_t moduleBase, uint8_t moduleFunction, const uint8_t *buf, uint8_t num)
{
    uint8_t data[2 + num];

    data[0] = moduleBase;
    data[1] = moduleFunction;

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

bool SeeSaw_read(uint8_t moduleBase, uint8_t moduleFunction, uint8_t *buf, uint8_t num, uint16_t delay)
{
    uint8_t data[2];
    data[0] = moduleBase;
    data[1] = moduleFunction;

    if (i2c_transmit(MY_I2C_ADDRESS, data, 2, 50) != 0) {
        return false;
    }
    wait_us(delay);

    if (i2c_receive(MY_I2C_ADDRESS, buf, num, 50) != 0) {
        return false;  
    }
    return true;
}
#ifndef RGB_DRIVER_H
#define RGB_DRIVER_H

#include "neopixel.h"
#include "print.h"

extern const rgb_matrix_driver_t rgb_matrix_driver;

void rgb_matrix_driver_init(void);
void rgb_matrix_driver_flush(void);
void rgb_matrix_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

#endif
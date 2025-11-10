#ifndef RGB_DRIVER_H
#define RGB_DRIVER_H

#include "neopixel.h"
#include "neotrellis.h"
#include "via_custom.h"
#include "print.h"

extern layer_color_config_t layer_color_config;

void rgb_matrix_driver_init(void);
void rgb_matrix_driver_flush(void);
void rgb_matrix_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
bool rgb_matrix_indicators_kb(void);

#endif
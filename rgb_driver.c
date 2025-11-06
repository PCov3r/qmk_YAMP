#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

#include "rgb_driver.h"

void rgb_matrix_driver_init(void) {
    i2c_init();
    Seesaw_neopixPin();
    Seesaw_neopixType();
    Seesaw_neopixLength();
}

void rgb_matrix_driver_flush(void) {
    Seesaw_neopixShow(); // Push color data to hardware
}

void rgb_matrix_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t brightness = 200;
    uint16_t n = index;
    print("TEST \n\n");
    Seesaw_neopixColor(n, red, green, blue, brightness);
}

void rgb_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t brightness = 200;
    Seesaw_neopixAllColor(red, green, blue, brightness);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = rgb_matrix_driver_init,
    .flush         = rgb_matrix_driver_flush,
    .set_color     = rgb_matrix_driver_set_color,
    .set_color_all = rgb_matrix_driver_set_color_all,
};

#endif
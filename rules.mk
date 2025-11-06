# Enable I2C and custom matrix
# CUSTOM_MATRIX = yes
# SRC += matrix_seesaw.c
CUSTOM_MATRIX = lite
SRC += matrix.c seesaw.c neotrellis.c neopixel.c rgb_driver.c

# Enable I2C subsystem
I2C_DRIVER_REQUIRED = yes

RGB_MATRIX_ENABLE = yes

# Enable debug
CONSOLE_ENABLE = yes
DEBUG_ENABLE = yes
SERIAL_DRIVER = vendor

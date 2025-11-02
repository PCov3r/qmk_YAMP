
#include "seesaw.h"
#include "print.h"

#define KEYPAD_BASE 0x10

#define KEYPAD_STATUS  0x00
#define KEYPAD_EVENT  0x01
#define KEYPAD_INTENSET  0x02
#define KEYPAD_INTENCLR  0x03
#define KEYPAD_COUNT  0x04
#define KEYPAD_FIFO  0x10

#define NEO_TRELLIS_NUM_ROWS 4
#define NEO_TRELLIS_NUM_COLS 4
#define NEO_TRELLIS_NUM_KEYS (NEO_TRELLIS_NUM_ROWS * NEO_TRELLIS_NUM_COLS)

typedef union {
  struct {
    uint8_t STATE : 1;  ///< the current state of the key
    uint8_t ACTIVE : 4; ///< the registered events for that key
  } bit;                ///< bitfield format
  uint8_t reg;          ///< register format
} keyState;

typedef union {
  struct {
    uint8_t EDGE : 2; ///< the edge that was triggered
    uint8_t NUM : 6;  ///< the event number
  } bit;              ///< bitfield format
  uint8_t reg;        ///< register format
} keyEventRaw;

#define NEO_TRELLIS_KEY(x) (((x) / 4) * 8 + ((x) % 4))
#define NEO_TRELLIS_SEESAW_KEY(x) (((x) / 8) * 4 + ((x) % 8))

void Seesaw_enableKeypadInterrupt(void);
void Seesaw_setKeypadEvent(uint8_t key, uint8_t edge, bool enable);
void Seesaw_activateKey(uint8_t key, uint8_t edge, bool enable);
uint8_t Seesaw_getKeypadCount(void);
bool Seesaw_readKeypad(keyEventRaw *buf, uint8_t count) ;
void Seesaw_readTrellis(bool polling);

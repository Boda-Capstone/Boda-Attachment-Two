#include <stdio.h>
#include "pico/stdlib.h"
#include "stdbool.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#ifndef SSD1306
#define SSD1306_H

#define BIT(X) (1 << X)

#define SSD1306_SLAVE_ADDRESS 0b0111100
#define SSD1306_ADDRESS_BYTE 0b01111000
#define SSD1306_CTRL_BYTE 0b00000000
#define DC_SET(X) (X << 6)
#define RW_SET(X) (X << 0)
#define UINT8_T(X) ((uint8_t)X)

typedef struct
{
    uint8_t dataBuffer[128][8];
    uint8_t commandBuffer[16];
    i2c_inst_t *i2c;
} SSD1306;

void initSSD1306(SSD1306 *s, i2c_inst_t *i2c);
void setDataBuffer(SSD1306 *s, uint8_t arr[128][8]);
void writeCommand(SSD1306 *s, uint8_t cmd, uint8_t *data, uint8_t l);
void writeDisplay(SSD1306 *s);
void insertSmallChar(SSD1306 *s, uint8_t* charArray, uint8_t x, uint8_t y);
void insertLargeChar(SSD1306 *s, uint8_t* charArray);
void getSmallChar(char c, uint8_t* charArray);
void getLargeChar(char c, uint8_t charArray[10][2]);
void writeLineCenter();
void writeLineLeft();
void writeLineRight();
#endif
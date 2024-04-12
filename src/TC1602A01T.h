#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#ifndef TC1602A01T_H
#define TC1602A01T_H

typedef struct
{
    uint8_t dataPINS[8];
    uint8_t CS_PIN;
    uint8_t RS_PIN;
    char display[32];
} TC1602A01T;

void initTC1602A01T(TC1602A01T *t, uint8_t *pins);
void sendCommand(TC1602A01T *t, uint8_t data);
void sendCharacter(TC1602A01T *t, char c);
void sendString(TC1602A01T *t, char* c, uint8_t l);
void updateDisplay(TC1602A01T *t, uint8_t *arr);
void setDisplay(TC1602A01T *t);
void clear(TC1602A01T *t);

#endif
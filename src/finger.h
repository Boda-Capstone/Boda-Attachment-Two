#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "servo.h"
#ifndef FINGER_H
#define FINGER_H

typedef struct
{
    Servo *top;
    Servo *bot;
} Finger;

void initFinger(Finger *f, Servo *s1, Servo *s2);
void extendWhole(Finger *f, uint16_t val);
void extendTop(Finger *f, uint16_t val);
void extendBottom(Finger *f, uint16_t val);

void retractWhole(Finger *f, uint16_t val);
void retractTop(Finger *f, uint16_t val);
void retractBottom(Finger *f, uint16_t val);

#endif
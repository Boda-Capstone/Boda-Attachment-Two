#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#ifndef SERVO_H
#define SERVO_H

#define MAX16 65535
#define MIN16 0
#define ANGLE_SLOPE (65535) / (180)
#define SERVO_SPEED 1

/**
 * SERVO TODO:
 *  - Make speeds ^ automatically calculated when the max and min are put in.
 *      - lo speed : 1% max
 *      - me speed : 3% max
 *      - hi speed : 5% max
 */

typedef struct
{
    // Number of the pin the PWM is connected to
    uint8_t pinNum;
    // Pointer to another variable where input data is stored
    uint16_t *input;
    // Number of the rp2040's PWM automatically determined slice
    uint8_t sliceNum;
    // Current PWM value for the servo
    uint16_t pwm;

    // The following variables are used in Mapping calculations to map the input range to the output pwm range
    // Maximum value that input can be
    uint16_t max;
    // Minimum value that input can be
    uint16_t min;
    // Automatically calculated linear slope used in mapping function
    uint16_t slope;

    // Automatically determined servo speeds TESTING
    uint16_t LO;
    uint16_t MD;
    uint16_t HI;
    // User set min limit on serbo position
    uint16_t limit_min;
    // User set max limit on servo position
    uint16_t limit_max;

    // The servos being used are 180 degrees, this lets us know what way they are facing
    // so that the proper calculations can be done
    // 1 indicates : Clockwise
    // 0 indicates : Counter Clockwise
    bool dir;
} Servo;

void initServo(Servo *s, uint8_t pin, uint16_t *inPtr, float clkDiv, uint16_t pwmLevel, bool dir);
void initServoMapping(Servo *s, uint16_t max, uint16_t min);
void setServoLimits(Servo *s, uint16_t max, uint16_t min);
uint8_t calcAngle(Servo *s);
void incrementPWM(Servo *s, uint16_t val);
void decrementPWM(Servo *s, uint16_t val);
void open(Servo *s, uint16_t val);
void close(Servo *s, uint16_t val);
void inputPWM(Servo *s);
void updatePWM(Servo *s);

#endif
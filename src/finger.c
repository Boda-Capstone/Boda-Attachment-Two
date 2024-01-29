#include "finger.h"


/**
 * FUNCTION: initFinger
 * Initializes a Finger instance
 * -------------------------------------------
 * PARAMETERS:
 * f  : Pointer to finger
 * s1 : Pointer to servo located near the top of the finger
 * s2 : Pointer to servo located near the bottom of the finger
 * -------------------------------------------
 * RETURNS: void
 */
void initFinger(Finger *f, Servo *s1, Servo *s2)
{
    f->top = s1;
    f->bot = s2;
}

/**
 * FUNCTION: extendWhole
 * Extends finger by calling Servo::open on both servos of the finger
 * -------------------------------------------
 * PARAMETERS:
 * f   : Pointer to finger
 * val : uint16_t value to move both fingers' servos' pwm by
 * -------------------------------------------
 * RETURNS: Void
 */
void extendWhole(Finger *f, uint16_t val)
{
    open(f->top, val);
    open(f->bot, val);
}

/**
 * FUNCTION: extendTop
 * Extends top of finger by calling Servo::open on servo labeled 'top'
 * -------------------------------------------
 * PARAMETERS:
 * f   : Pointer to finger
 * val : uint16_t value to move top finger's servo pwm by
 * -------------------------------------------
 * RETURNS: Void
 */
void extendTop(Finger *f, uint16_t val)
{
    open(f->top, val);
}

/**
 * FUNCTION: extendBottom
 * Extends bottom of finger by calling Servo::open on servo labeled 'bot'
 * -------------------------------------------
 * PARAMETERS:
 * f   : Pointer to finger
 * val : uint16_t value to move bottom finger's servo pwm by
 * -------------------------------------------
 * RETURNS: Void
 */
void extendBottom(Finger *f, uint16_t val)
{
    open(f->bot, val);
}

/**
 * FUNCTION: retractWhole
 * Retracts finger by calling Servo::close on both servos of the finger
 * -------------------------------------------
 * PARAMETERS:
 * f   : Pointer to finger
 * val : uint16_t value to move both fingers' servos' pwm by
 * -------------------------------------------
 * RETURNS: Void
 */
void retractWhole(Finger *f, uint16_t val)
{
    close(f->top, val);
    close(f->bot, val);
}

/**
 * FUNCTION: retractTop
 * Retracts top of finger by calling Servo::close on servo labeled 'top'
 * -------------------------------------------
 * PARAMETERS:
 * f   : Pointer to finger
 * val : uint16_t value to move top finger's servo pwm by
 * -------------------------------------------
 * RETURNS: Void
 */
void retractTop(Finger *f, uint16_t val)
{
    close(f->top, val);
}

/**
 * FUNCTION: retractBottom
 * Retracts bottom of finger by calling Servo::close on servo labeled 'bot'
 * -------------------------------------------
 * PARAMETERS:
 * f   : Pointer to finger
 * val : uint16_t value to move top finger's servo pwm by
 * -------------------------------------------
 * RETURNS: Void
 */
void retractBottom(Finger *f, uint16_t val)
{
    close(f->bot, val);
}
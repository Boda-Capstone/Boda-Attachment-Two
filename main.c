#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "src/servo.h"
#include "src/finger.h"

// Global Variables
uint8_t rec = 0xFF;
uint8_t tra = 0x64;
uint8_t input = 0;
uint8_t oldput = 0;

// Array containint list of all initialized servos
// NOTE: Only 8 servos can be initialized at a time
Servo servos[8];
uint16_t servoPWMS[8];
uint8_t numServos = 0;

/**
 * FUNCTION:
 * -------------------------------------------
 * PARAMETERS:
 *
 * -------------------------------------------
 * RETURNS:
 *
 */

/**
 * TODO:
 *  - Verify get angle works
 *  - add a delete servo function to free gpio pins
 *  - Create an SPI input for controllers
 *      - have it trigger an interrupt to update the value, this can be easiy checked with UART
 *  - Actually connect the servos
 *  - Research amps needed to control the servos while in motion
 *  - put it on tiny breadboard
 *  - have preprogrammed motions
 *      - Open, Close, Grab, Let Go
 *      - have an options to switch to joystick controls.
 *
 *  - Pitch idea of mode switching where a button/combo is pressed to route all controls to the attachment
 *  - ADD 360 DEGREE SERVO SUPPORT
 */

/**
 * FUNCTION: pwm_irq_handler
 * This function is set to be called anytime ANY pwm interrupt goes off.
 * Determines which pwm slice was triggered from the list of initialized servos
 * and calls pwm_irq to update its pwm level
 * -------------------------------------------
 * PARAMETERS: N/A
 *
 * -------------------------------------------
 * RETURNS: Void
 */
void pwm_irq_handler()
{
    uint8_t status = pwm_get_irq_status_mask();
    for (uint8_t i = 0; i < numServos; i++)
    {
        // if the status bit for the pwm slice has been set (an interrupt was triggered for the pwm slice)
        if (status & (1 << servos[i].sliceNum))
        {
            // set the pwm level of the servo whose interrupt was triggered
            updatePWM(&servos[i]);
            // clear the status bit
            pwm_clear_irq(pwm_gpio_to_slice_num(i));
        }
    }
}

/**
 * FUNCTION: pwm_irq_init
 * Called at the start of main to enable interrupts and
 * sets pwm to be able to trigger interrupts
 * -------------------------------------------
 * PARAMETERS: N/A
 * -------------------------------------------
 * RETURNS: Void
 */
void pwm_irq_init()
{
    irq_set_mask_enabled(PWM_IRQ_WRAP, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_irq_handler);
    irq_set_enabled(PWM_IRQ_WRAP, true);
}

void spi_irq()
{
    spi_write_read_blocking(spi_default, (uint8_t *)&oldput, (uint8_t *)&input, 1);
    oldput = input;
}

void spi_irq_init()
{
    spi0_hw->imsc = 1 << 2;
    irq_set_exclusive_handler(SPI0_IRQ, spi_irq);
    irq_set_enabled(SPI0_IRQ, true);
}

int main()
{
    stdio_init_all();

    // initialize adc for the potentiometer
    adc_init();
    // select the current adc channel to get input from.
    adc_select_input(0);

    // intialize pwm irq for servos
    pwm_irq_init();

    // initialize SPI
    spi_init(spi_default, 2 * 1000 * 1000);
    spi_set_format(spi_default, 8, 1, 0, true);
    spi_set_slave(spi_default, true);

    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);

    // initialize spi irq for control data
    spi_irq_init();

    // // Initialize two servos for finger 1
    initServo(&servos[0], 0, &servoPWMS[0], 4.f, 8193, MD, 0);
    //initServoMapping(&servos[0], 4095, 0);
    setServoLimits(&servos[0], MAX16 / 2, 8192);
    numServos++;

    initServo(&servos[1], 1, &servoPWMS[1], 4.f, MAX16 - 8191, MD, 1);
    //initServoMapping(&servos[1], 4095, 0);
    setServoLimits(&servos[1], MAX16 - 8192, MAX16 / 2);
    numServos++;

    Finger leftFinger;
    initFinger(&leftFinger, &servos[0], &servos[1]);

    initServo(&servos[2], 2, &servoPWMS[2], 4.f, MAX16 - 8191, MD, 1);
    //initServoMapping(&servos[2], 4095, 0);
    setServoLimits(&servos[2], MAX16 - 8192, MAX16 / 2);
    numServos++;

    initServo(&servos[3], 3, &servoPWMS[3], 4.f, 8193, MD, 0);
    //initServoMapping(&servos[3], 4095, 0);
    setServoLimits(&servos[3], MAX16 / 2, 8192);
    numServos++;

    Finger rightFinger;
    initFinger(&rightFinger, &servos[2], &servos[3]);

    while (1)
    {
        if (input & 0b00001000)
        {
            extendBottom(&leftFinger, HI);
            extendBottom(&rightFinger, HI);
        }
        if (input & 0b00000100)
        {
            retractBottom(&leftFinger, HI);
            retractBottom(&rightFinger, HI);
        }
        if (input & 0b00000010)
        {
            extendTop(&leftFinger, HI);
            extendTop(&rightFinger, HI);
        }
        if (input & 0b00000001)
        {
            retractTop(&leftFinger, HI);
            retractTop(&rightFinger, HI);
        }
        input = 0;
    }
}
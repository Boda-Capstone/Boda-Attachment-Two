#include "Attachment.h"

uint16_t att_input;
uint16_t att_output = 0x01;
uint16_t WHO_AM_I = 'DA';
uint8_t buttons[8] = {ATT_X, ATT_CIRCLE, ATT_TRIANGLE, ATT_SQUARE, ATT_R1, ATT_R2, ATT_L1, ATT_L2};

/**
 * FUNCTION:
 *
 * -------------------------------------------
 * PARAMETERS:
 *
 * -------------------------------------------
 * RETURNS:
 *
 */

/**
 * FUNCTION: initAttachment
 * Initializes instance of attachment struct
 * -------------------------------------------
 * PARAMETERS:
 * a : Pointer to attachment
 * -------------------------------------------
 * RETURNS:
 * Void
 */
void initAttachment(Attachment *a)
{
    a->buttonStatus = &att_input;

    a->buttonFunctions[0] = buttonOneFunction;
    a->buttonFunctions[1] = buttonTwoFunction;
    a->buttonFunctions[2] = buttonThreeFunction;
    a->buttonFunctions[3] = buttonFourFunction;
    a->buttonFunctions[4] = buttonFiveFunction;
    a->buttonFunctions[5] = buttonSixFunction;
    a->buttonFunctions[6] = buttonSevenFunction;
    a->buttonFunctions[7] = buttonEightFunction;

    // initialize SPI
    spi_init(spi_default, 1000 * 1000);
    spi_set_format(spi_default, 16, 1, 0, true);
    spi_set_slave(spi_default, true);

    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);

    // initialize spi irq for control data
    spi_irq_init();
}

/**
 * FUNCTION: pollButtonFunctions
 * When called, polls each bit in attachment's buttonStatus,
 * if the bit is set, execute the corresponding buttonFunction
 * -------------------------------------------
 * PARAMETERS:
 * a : Attachment to Poll
 * -------------------------------------------
 * RETURNS:
 * Void
 */
void pollButtonFunctions(Attachment *a)
{
    for (int i = 0; i < 8; i++)
    {
        if (*(a->buttonStatus) & (1 << i))
        {
            // if the buttons isnt meant to be held:

            (a->buttonFunctions[i])();

            uint16_t temp = 0b1111111111111111;
            temp ^= (1 << i);
            *(a->buttonStatus) &= temp;
        }
    }
}

/**
 * FUNCTION: spi_irq
 * Triggers on incoming SPI transaction, reads incoming
 * byte and sends one byte
 * !!NOT meant to be called by user, but can be edited by user if necessary
 * -------------------------------------------
 * PARAMETERS:
 * N/A
 * -------------------------------------------
 * RETURNS:
 * Void
 */
void spi_irq()
{
    spi_write16_read16_blocking(spi_default, (uint16_t *)&att_output, (uint16_t *)&att_input, 1);
    att_output = 0x01;
    if ((uint8_t)((att_input >> 8) & 0xFF) != 0)
    {
        switch ((uint8_t)((att_input >> 8) & 0xFF))
        {
        case 0x01:
            att_output = (uint16_t)buttons[0];
            att_output |= ((uint16_t)buttons[1] << 8);
            break;
        case 0x02:
            att_output = (uint16_t)buttons[2];
            att_output |= ((uint16_t)buttons[3] << 8);
            break;
        case 0x03:
            att_output = (uint16_t)buttons[4];
            att_output |= ((uint16_t)buttons[5] << 8);
            break;
        case 0x04:
            att_output = (uint16_t)buttons[6];
            att_output |= ((uint16_t)buttons[7] << 8);
            break;
        case 0x05:
            break;
        case 0x0C:
            att_output = 0x01;
            break;
        case 0x0D:
            break;
        case 0x0E:
            att_output = 0xAA;
        case 0x64:
            att_output = WHO_AM_I;
            break;
        default:
            break;
        }
        uint16_t temp = 0b1111111111111111;
        temp ^= 0xF0;
        att_input &= temp;
    }
}

/**
 * FUNCTION: spi_irq_init
 * Initialization for SPI IRQ
 * !!To be called after an attachment has been initialized
 * -------------------------------------------
 * PARAMETERS:
 * N/A
 * -------------------------------------------
 * RETURNS:
 * Void
 */
void spi_irq_init()
{
    spi0_hw->imsc = 1 << 2;
    irq_set_exclusive_handler(SPI0_IRQ, spi_irq);
    irq_set_enabled(SPI0_IRQ, true);
}
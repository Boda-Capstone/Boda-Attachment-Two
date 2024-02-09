#include "Attachment.h"

uint8_t *ptrInput;
uint8_t *ptrOutput;

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
            (a->buttonFunctions[i])();
            uint8_t temp = 0b11111111;
            temp ^= (1 << i);
            *(a->buttonStatus) &= temp;
        }
    }
}

/**
 * FUNCTION: initAttachment
 * Initializes instance of attachment struct
 * -------------------------------------------
 * PARAMETERS:
 * a          : Pointer to attachment
 * statusByte : pointer to 
 * -------------------------------------------
 * RETURNS:
 *
 */
void initAttachment(Attachment *a, uint8_t *statusByte)
{
    a->buttonStatus = statusByte;

    a->buttonFunctions[0] = buttonOneFunction;
    a->buttonFunctions[1] = buttonTwoFunction;
    a->buttonFunctions[2] = buttonThreeFunction;
    a->buttonFunctions[3] = buttonFourFunction;
    a->buttonFunctions[4] = buttonFiveFunction;
    a->buttonFunctions[5] = buttonSixFunction;
    a->buttonFunctions[6] = buttonSevenFunction;
    a->buttonFunctions[7] = buttonEightFunction;

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
}

void spi_irq()
{
    spi_write_read_blocking(spi_default, ptrOutput, ptrInput, 1);
}

void spi_irq_init()
{
    spi0_hw->imsc = 1 << 2;
    irq_set_exclusive_handler(SPI0_IRQ, spi_irq);
    irq_set_enabled(SPI0_IRQ, true);
}
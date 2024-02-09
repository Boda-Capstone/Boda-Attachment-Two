#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#ifndef ATT_INPUT
#define ATT_INPUT
extern uint8_t att_input;
#endif

#ifndef ATT_OUTPUT
#define ATT_OUTPUT
extern uint8_t att_output;
#endif

typedef void (*buttonFunction)(void);

typedef struct
{
    uint8_t *buttonStatus;
    buttonFunction buttonFunctions[8];
} Attachment;

void initAttachment(Attachment *a);
void pollButtonFunctions(Attachment *a);
void spi_irq_init();
void spi_irq();

//----------Button Function Declarations for User to Define----------//
void buttonOneFunction();
void buttonTwoFunction();
void buttonThreeFunction();
void buttonFourFunction();
void buttonFiveFunction();
void buttonSixFunction();
void buttonSevenFunction();
void buttonEightFunction();

#endif
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#ifndef ATTACHMENT_H
#define ATTACHMENT_H

#ifndef IN_PTR
#define IN_PTR
extern uint8_t *ptrInput;
#endif

#ifndef OUT_PTR
#define OUT_PTR
extern uint8_t *ptrOutput;
#endif

typedef void (*buttonFunction)(void);

typedef struct
{
    uint8_t *buttonStatus;
    buttonFunction buttonFunctions[8];
} Attachment;

void initAttachment(Attachment *a, uint8_t *statusByte);
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
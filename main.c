#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "src/Attachment.h"
#include "src/SSD1306.h"

#define MUXA 14
#define MUXB 15

Attachment a;
SSD1306 s[4];

void initMux()
{
    gpio_init(MUXA);
    gpio_init(MUXB);
    gpio_set_dir(MUXA, GPIO_OUT);
    gpio_set_dir(MUXB, GPIO_OUT);
    gpio_put(MUXA, 0);
    gpio_put(MUXB, 0);
}

void setMux(uint8_t n)
{
    if (n > 3)
    {
        gpio_put(MUXA, 1);
        gpio_put(MUXB, 1);
        return;
    }
    gpio_put(MUXA, n & 0x01);
    gpio_put(MUXB, (n >> 1) & 0x01);
}

int main()
{
    stdio_init_all();

    initAttachment(&a);

    // User Code Init Begin
    initMux();
    for (int i = 0; i < 4; i++)
    {
        setMux(i);
        initSSD1306(&s[i]);
    }
    
    // User Code Init End

    while (1)
    {
        pollButtonFunctions(&a);
        // User Code While Loop Begin



        //  User Code While Loop End
    }
}

//----------Button Function Definitions For Each Button's Actions----------//

// Button One Function
void buttonOneFunction()
{
    return;
}

// Button Two Function
void buttonTwoFunction()
{
    return;
}

// Button Three Function
void buttonThreeFunction()
{
    return;
}

// Button Four Function
void buttonFourFunction()
{
    return;
}

// Button Five Function
void buttonFiveFunction()
{
    return;
}

// Button Six Function
void buttonSixFunction()
{
    return;
}

// Button Seven Function
void buttonSevenFunction()
{
    return;
}

// Button Eight Function
void buttonEightFunction()
{
    return;
}
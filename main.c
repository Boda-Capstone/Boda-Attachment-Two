#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "src/Attachment.h"

Attachment a;

int main()
{

    stdio_init_all();

    initAttachment(&a);

    //User Code Init Begin


    //User Code Init End
    
    while (1)
    {
        pollButtonFunctions(&a);
        //User Code While Loop Begin

        
        //User Code While Loop End
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
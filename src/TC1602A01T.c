#include "TC1602A01T.h"

uint8_t char2lcd(char c);

void initTC1602A01T(TC1602A01T *t, uint8_t *pins)
{
    for (int i = 0; i < 32; i++)
    {
        t->display[i] = '0';
    }
    for (int i = 0; i < 10; i++)
    {
        gpio_init((*pins));
        gpio_set_dir((*pins), GPIO_OUT);
        gpio_put((*pins), 0);
        if (i < 8)
        {
            t->dataPINS[i] = (*pins);
            pins++;
        }
        else if (i == 8)
        {
            t->CS_PIN = (*pins);
            pins++;
        }
        else
        {
            t->RS_PIN = (*pins);
        }
    }
    sleep_ms(15);
    // set lcd to 8 bit mode
    sendCommand(t, (uint8_t)0b00001100);
    // wait 4.1 ms
    sleep_us(4100);
    sendCommand(t, (uint8_t)0b00001100);
    sleep_us(100);
    sendCommand(t, (uint8_t)0b00001100);
    sleep_ms(100);

    sendCommand(t, (uint8_t)0b00011100);
    sendCommand(t, (uint8_t)0b01110000);
    sendCommand(t, (uint8_t)0b11100000);
    //sendCommand(t, (uint8_t)0b01100000);
    //sendCommand(t, (uint8_t)0b11110000);
    setDisplay(t);
}

void sendCommand(TC1602A01T *t, uint8_t data)
{
    // set the RS pin
    gpio_put(t->RS_PIN, 0);
    // set the 8 data pins
    for (int i = 0; i < 8; i++)
    {
        gpio_put(t->dataPINS[i], (uint8_t)(data >> i) & 0x01);
    }

    // enable
    gpio_put(t->CS_PIN, 1);
    sleep_ms(5);
    // disable
    gpio_put(t->CS_PIN, 0);
}

void sendCharacter(TC1602A01T *t, char c)
{
    uint8_t data = char2lcd(c);
    // set the RS pin
    gpio_put(t->RS_PIN, 1);
    // set the 8 data pins
    for (int i = 0; i < 8; i++)
    {
        gpio_put(t->dataPINS[i], (uint8_t)(data >> i) & 0x01);
    }

    // enable
    gpio_put(t->CS_PIN, 1);
    // wait
    sleep_ms(5);
    // disable
    gpio_put(t->CS_PIN, 0);
}

void updateDisplay(TC1602A01T *t, uint8_t *arr)
{
    for (int i = 0; i < 32; i++)
    {
        t->display[i] = arr[i];
    }
}

void setDisplay(TC1602A01T *t)
{
    // clear screen
    sendCommand(t, (uint8_t)0b00000001);
    for (int i = 0; i < 32; i++)
    {
        if (i == 16)
        {
            // change lines
            sendCommand(t, (uint8_t)0b00000000);
        }
        sendCharacter(t, t->display[i]);
    }
}

void sendString(TC1602A01T *t, char *c, uint8_t l)
{
    for (int i = 0; i < l; i++)
    {
        sendCharacter(t, c[i]);
    }
}

uint8_t char2lcd(char c)
{
    switch (c)
    {
    case 'a':
    case 'A':
        return 0x41;
        break;
    case 'b':
    case 'B':
        return 0x42;
        break;
    case 'c':
    case 'C':
        return 0x43;
        break;
    case 'd':
    case 'D':
        return 0x44;
        break;
    case 'e':
    case 'E':
        return 0x45;
        break;
    case 'f':
    case 'F':
        return 0x46;
        break;
    case 'g':
    case 'G':
        return 0x47;
        break;
    case 'h':
    case 'H':
        return 0x48;
        break;
    case 'i':
    case 'I':
        return 0x49;
        break;
    case 'j':
    case 'J':
        return 0x4A;
        break;
    case 'k':
    case 'K':
        return 0x4B;
        break;
    case 'l':
    case 'L':
        return 0x4C;
        break;
    case 'm':
    case 'M':
        return 0x4D;
        break;
    case 'n':
    case 'N':
        return 0x4E;
        break;
    case 'o':
    case 'O':
        return 0x4F;
        break;
    case 'p':
    case 'P':
        return 0x50;
        break;
    case 'q':
    case 'Q':
        return 0x51;
        break;
    case 'r':
    case 'R':
        return 0x52;
        break;
    case 's':
    case 'S':
        return 0x53;
        break;
    case 't':
    case 'T':
        return 0x54;
        break;
    case 'u':
    case 'U':
        return 0x55;
        break;
    case 'v':
    case 'V':
        return 0x56;
        break;
    case 'w':
    case 'W':
        return 0x57;
        break;
    case 'x':
    case 'X':
        return 0x58;
        break;
    case 'y':
    case 'Y':
        return 0x59;
        break;
    case 'z':
    case 'Z':
        return 0x5A;
        break;
    case '1':
        return 0x31;
        break;
    case '2':
        return 0x32;
        break;
    case '3':
        return 0x33;
        break;
    case '4':
        return 0x34;
        break;
    case '5':
        return 0x35;
        break;
    case '6':
        return 0x36;
        break;
    case '7':
        return 0x37;
        break;
    case '8':
        return 0x38;
        break;
    case '9':
        return 0x39;
        break;
    case '0':
        return 0x30;
        break;
    default:
        return 0x21;
        break;
    }
    return 0;
}
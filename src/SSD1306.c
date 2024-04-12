#include "SSD1306.h"

uint8_t tempBuffer[1025];

void initSSD1306(SSD1306 *s, i2c_inst_t *i2c)
{
    s->i2c = i2c;
    i2c_init(i2c, 1000 * 100);
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            s->dataBuffer[i][j] = 0x00;
        }
        if (i < 16)
        {
            s->commandBuffer[i] = 0;
        }
    }

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    sleep_ms(1);
    uint8_t t[2];

    // Set Multiplex Ratio to 63 (MAX)
    t[0] = 0x3F;
    writeCommand(s, 0xA8, t, 1);

    // Set Display Offset to 0
    t[0] = 0x00;
    writeCommand(s, 0xD3, t, 1);

    // Set Start Line
    writeCommand(s, 0x40, 0, 0);

    // Set Segment Remap: col 0 is seg127
    writeCommand(s, 0xA1, 0, 0);

    // Set COM Output Scan Direction
    writeCommand(s, 0xC8, 0, 0);

    // Set COM Pin Hardware Configuration
    t[0] = 0x12;
    writeCommand(s, 0xDA, t, 1);

    // Set Contrast
    t[0] = 0x7F;
    writeCommand(s, 0x81, t, 1);

    // Resume Display
    writeCommand(s, 0xA4, 0, 0);

    // Set Normal Display
    writeCommand(s, 0xA6, 0, 0);

    // Set Oscillator Frequency
    t[0] = 0x80;
    writeCommand(s, 0xD5, t, 1);

    // Enable Charge Pump
    t[0] = 0x14;
    writeCommand(s, 0x8D, t, 1);

    // Display On
    writeCommand(s, 0xAF, 0, 0);

    // Set Adressing Mode
    t[0] = 0x00;
    writeCommand(s, 0x20, t, 1);

    // Set the Start and End Column Addresses
    t[0] = 0;
    t[1] = 127;
    writeCommand(s, 0x21, t, 2);

    // Set the Start and End Row Addresses
    t[0] = 0;
    t[1] = 7;
    writeCommand(s, 0x22, t, 2);

    writeDisplay(s);
}

void setDataBuffer(SSD1306 *s, uint8_t arr[128][8])
{
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            s->dataBuffer[i][j] = arr[i][j];
        }
    }
}

void writeCommand(SSD1306 *s, uint8_t cmd, uint8_t *data, uint8_t l)
{
    s->commandBuffer[0] = SSD1306_CTRL_BYTE;
    s->commandBuffer[1] = cmd;
    if (l > 0)
    {
        for (int i = 2; i <= l + 1; i++)
        {
            s->commandBuffer[i] = data[i - 2];
        }
    }
    i2c_write_blocking(s->i2c, SSD1306_SLAVE_ADDRESS, s->commandBuffer, l + 2, 0);
}

void writeDisplay(SSD1306 *s)
{
    tempBuffer[0] = SSD1306_CTRL_BYTE | DC_SET(1);
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tempBuffer[(j * 128) + i + 1] = s->dataBuffer[i][j];
        }
    }
    i2c_write_blocking(s->i2c, SSD1306_SLAVE_ADDRESS, tempBuffer, 1025, 0);
}

void insertSmallChar(SSD1306 *s, uint8_t *charArray, uint8_t x, uint8_t y)
{
}

void insertLargeChar(SSD1306 *s, uint8_t *charArray)
{
}

void getSmallChar(char c, uint8_t *charArray)
{
    switch (c)
    {
    case 'a':
    case 'A':
        charArray[0] = 0x70;
        charArray[1] = 0x2E;
        charArray[2] = 0x21;
        charArray[3] = 0x2E;
        charArray[4] = 0x70;
        break;
    case 'b':
    case 'B':
        charArray[0] = 0x7F;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x4E;
        charArray[4] = 0x30;
        break;
    case 'c':
    case 'C':
        charArray[0] = 0x3E;
        charArray[1] = 0x41;
        charArray[2] = 0x41;
        charArray[3] = 0x41;
        charArray[4] = 0x22;
        break;
    case 'd':
    case 'D':
        charArray[0] = 0x7F;
        charArray[1] = 0x41;
        charArray[2] = 0x41;
        charArray[3] = 0x41;
        charArray[4] = 0x3E;
        break;
    case 'e':
    case 'E':
        charArray[0] = 0x7F;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x41;
        break;
    case 'f':
    case 'F':
        charArray[0] = 0x7F;
        charArray[1] = 0x09;
        charArray[2] = 0x09;
        charArray[3] = 0x09;
        charArray[4] = 0x01;
        break;
    case 'g':
    case 'G':
        charArray[0] = 0x3E;
        charArray[1] = 0x41;
        charArray[2] = 0x41;
        charArray[3] = 0x49;
        charArray[4] = 0x3A;
        break;
    case 'h':
    case 'H':
        charArray[0] = 0x7F;
        charArray[1] = 0x08;
        charArray[2] = 0x08;
        charArray[3] = 0x08;
        charArray[4] = 0x7F;
        break;
    case 'i':
    case 'I':
        charArray[0] = 0x41;
        charArray[1] = 0x41;
        charArray[2] = 0x7F;
        charArray[3] = 0x41;
        charArray[4] = 0x41;
        break;
    case 'j':
    case 'J':
        charArray[0] = 0x41;
        charArray[1] = 0x41;
        charArray[2] = 0x3F;
        charArray[3] = 0x01;
        charArray[4] = 0x01;
        break;
    case 'k':
    case 'K':
        charArray[0] = 0x7F;
        charArray[1] = 0x08;
        charArray[2] = 0x14;
        charArray[3] = 0x22;
        charArray[4] = 0x41;
        break;
    case 'l':
    case 'L':
        charArray[0] = 0x7F;
        charArray[1] = 0x40;
        charArray[2] = 0x40;
        charArray[3] = 0x40;
        charArray[4] = 0x40;
        break;
    case 'm':
    case 'M':
        charArray[0] = 0x7F;
        charArray[1] = 0x06;
        charArray[2] = 0x08;
        charArray[3] = 0x06;
        charArray[4] = 0x7F;
        break;
    case 'n':
    case 'N':
        charArray[0] = 0x7F;
        charArray[1] = 0x06;
        charArray[2] = 0x08;
        charArray[3] = 0x30;
        charArray[4] = 0x7F;
        break;
    case 'o':
    case 'O':
        charArray[0] = 0x3E;
        charArray[1] = 0x41;
        charArray[2] = 0x41;
        charArray[3] = 0x41;
        charArray[4] = 0x3E;
        break;
    case 'p':
    case 'P':
        charArray[0] = 0x3E7F;
        charArray[1] = 0x11;
        charArray[2] = 0x11;
        charArray[3] = 0x11;
        charArray[4] = 0x0E;
        break;
    case 'q':
    case 'Q':
        charArray[0] = 0x3E;
        charArray[1] = 0x41;
        charArray[2] = 0x51;
        charArray[3] = 0x61;
        charArray[4] = 0x7E;
        break;
    case 'r':
    case 'R':
        charArray[0] = 0x7F;
        charArray[1] = 0x11;
        charArray[2] = 0x11;
        charArray[3] = 0x11;
        charArray[4] = 0x6E;
        break;
    case 's':
    case 'S':
        charArray[0] = 0x46;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x31;
        break;
    case 't':
    case 'T':
        charArray[0] = 0x01;
        charArray[1] = 0x01;
        charArray[2] = 0x7F;
        charArray[3] = 0x01;
        charArray[4] = 0x01;
        break;
    case 'u':
    case 'U':
        charArray[0] = 0x3F;
        charArray[1] = 0x40;
        charArray[2] = 0x40;
        charArray[3] = 0x40;
        charArray[4] = 0x3F;
        break;
    case 'v':
    case 'V':
        charArray[0] = 0x0F;
        charArray[1] = 0x30;
        charArray[2] = 0x40;
        charArray[3] = 0x30;
        charArray[4] = 0x0F;
        break;
    case 'w':
    case 'W':
        charArray[0] = 0x0F;
        charArray[1] = 0x70;
        charArray[2] = 0x18;
        charArray[3] = 0x70;
        charArray[4] = 0x0F;
        break;
    case 'x':
    case 'X':
        charArray[0] = 0x63;
        charArray[1] = 0x14;
        charArray[2] = 0x08;
        charArray[3] = 0x14;
        charArray[4] = 0x63;
        break;
    case 'y':
    case 'Y':
        charArray[0] = 0x03;
        charArray[1] = 0x04;
        charArray[2] = 0x78;
        charArray[3] = 0x04;
        charArray[4] = 0x03;
        break;
    case 'z':
    case 'Z':
        charArray[0] = 0x61;
        charArray[1] = 0x51;
        charArray[2] = 0x49;
        charArray[3] = 0x45;
        charArray[4] = 0x43;
        break;
    case '0':
        charArray[0] = 0x3E;
        charArray[1] = 0x47;
        charArray[2] = 0x49;
        charArray[3] = 0x71;
        charArray[4] = 0x3E;
        break;
    case '1':
        charArray[0] = 0x00;
        charArray[1] = 0x42;
        charArray[2] = 0x7F;
        charArray[3] = 0x40;
        charArray[4] = 0x00;
        break;
    case '2':
        charArray[0] = 0x72;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x46;
        break;
    case '3':
        charArray[0] = 0x22;
        charArray[1] = 0x41;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x36;
        break;
    case '4':
        charArray[0] = 0x18;
        charArray[1] = 0x16;
        charArray[2] = 0x11;
        charArray[3] = 0x7F;
        charArray[4] = 0x10;
        break;
    case '5':
        charArray[0] = 0x2F;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x31;
        break;
    case '6':
        charArray[0] = 0x3E;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x32;
        break;
    case '7':
        charArray[0] = 0x01;
        charArray[1] = 0x61;
        charArray[2] = 0x11;
        charArray[3] = 0x09;
        charArray[4] = 0x07;
        break;
    case '8':
        charArray[0] = 0x36;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x36;
        break;
    case '9':
        charArray[0] = 0x26;
        charArray[1] = 0x49;
        charArray[2] = 0x49;
        charArray[3] = 0x49;
        charArray[4] = 0x3E;
        break;
    default:
        charArray[0] = 0xFF;
        charArray[1] = 0xFF;
        charArray[2] = 0xFF;
        charArray[3] = 0xFF;
        charArray[4] = 0xFF;
        break;
    }
}

void getLargeChar(char c, uint8_t charArray[10][2])
{
    uint8_t temp[5];
    getSmallChar(c, temp);
    // upscale

    // for each byte in the small character array
    for (int i = 0; i < 5; i++)
    {
        // for each bit in the byte, upscale it to the new array
        for (int j = 0; j < 8; j++)
        {
            uint8_t bit = (temp[i] >> j) & 0x01;
            if (bit == 1)
            {
                if (j < 4)
                {
                    charArray[2 * i][0] |= (0x03 << (j * 2));
                    charArray[(2 * i) + 1][0] |= (0x03 << (j * 2));
                }
                else
                {
                    charArray[2 * i][1] |= (0x03 << ((j % 4) * 2));
                    charArray[(2 * i) + 1][1] |= (0x03 << ((j % 4) * 2));
                }
            }
        }
    }
}
#ifndef I2C_H
#define I2C_H

#include <reg51.h>
sbit SDA = P0^0;
sbit SCL = P0^1;

void delay(unsigned int ms);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char dat);
unsigned char i2c_read_nack(void);

void delay(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void i2c_start(void)
{
    SDA = 1; SCL = 1;
    SDA = 0; SCL = 0;
}

void i2c_stop(void)
{
    SDA = 0; SCL = 1;
    SDA = 1;
}

void i2c_write(unsigned char dat)
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        SDA = (dat & 0x80) ? 1 : 0;
        SCL = 1;
        SCL = 0;
        dat <<= 1;
    }
    SDA = 1; SCL = 1; SCL = 0; // ACK bit
}

unsigned char i2c_read_nack(void)
{
    unsigned char i, dat = 0;
    SDA = 1;
    for(i = 0; i < 8; i++)
    {
        SCL = 1;
        dat = (dat << 1) | SDA;
        SCL = 0;
    }
    // NACK
    SDA = 1; SCL = 1; SCL = 0;
    return dat;
}

#endif

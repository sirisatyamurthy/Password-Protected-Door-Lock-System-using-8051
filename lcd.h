#include <reg51.h>
/*
	(0x38)	Initialize LCD in 8-bit mode, 2-line display, 5×7 font.
  (0x0E)	Turn display ON, cursor ON, blink OFF.
  (0x0C)	Turn display ON, cursor OFF, blink OFF.
  (0x01)	Clear the display and move cursor to home (position 0).
  (0x06)	Set entry mode – cursor moves right after each character.
  (0x80)	Move cursor to the beginning of the first line.
  (0xC0)	Move cursor to the beginning of the second line.
*/
sbit RS=P3^7;
sbit EN=P3^5;
sbit RW=P3^6;

void delay(unsigned int );
void lcd_cmd(unsigned char );
void lcd_data(unsigned char );
void writestring(unsigned char *);
void delay(unsigned int i)
{
unsigned int m;
unsigned int n;
for(m=0;m<i;m=m+1)
{
 for(n=0;n<275;n++);
 }
 }
 void lcd_cmd(unsigned char cmd)
 {
 P2=cmd;
 RS=0;
 EN=1;
 delay(2);
 EN=0;
 }
 void lcd_init()
 {
 lcd_cmd(0x38);
 lcd_cmd(0x0E);
 lcd_cmd(0x01);
 lcd_cmd(0x06);
 lcd_cmd(0x80);
 }
 void lcd_data(unsigned char dat)
 {
 P2=dat;
 RS=1;
 EN=1;
 delay(2);
 EN=0;
 }
void printString(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        lcd_data(str[i]);
        i++;
    }
}
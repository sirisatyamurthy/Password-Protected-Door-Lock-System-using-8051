#include <reg51.h>
#include "lcdpro.h"
#include "keypadpro.h"
#include "motorpro.h"

void check(void);
void wait(void);
void change_password(void);

unsigned char password[4] = {'1', '2', '3', '4'};  // default password
unsigned char entered[10];
unsigned char count = 0;
unsigned char attempts = 0;

void main(void)
{
    unsigned char key;
    lcd_init();
    motor_init();

    lcd_cmd(0x80);
    printString("PASSWORD PROTECT");
    lcd_cmd(0xC4);
    printString("SYSTEM");
    delay(800);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    printString("ENTER PASSWORD:");
    lcd_cmd(0xC0);

    while (1)
    {
        key = keyscan();

        if (key >= '0' && key <= '9')
        {
            if (count < 10)   // allow multiple digits before #
            {
                entered[count++] = key;
                lcd_data('*');
            }
        }
        else if (key == '*')   // Clear input
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            printString("ENTER PASSWORD:");
            lcd_cmd(0xC0);
            count = 0;
        }
        else if (key == '#')   // Enter pressed
        {
            // If the user entered *440# sequence, trigger password change mode
            if (count == 3 && entered[0] == '4' && entered[1] == '4' && entered[2] == '0')
            {
                change_password();
            }
            else if (count == 4)
            {
                check();
            }
            else
            {
                lcd_cmd(0x01);
                printString("PASSWORD WRONG");
                delay(600);
            }

            // Reset for next input
            count = 0;
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            printString("ENTER PASSWORD:");
            lcd_cmd(0xC0);
        }
    }
}

// ====== Check if entered password matches ======
void check(void)
{
    if (entered[0] == password[0] && entered[1] == password[1] &&
        entered[2] == password[2] && entered[3] == password[3])
    {
        lcd_cmd(0x01);
        printString("PASSWORD MATCH");
        
        motor_unlock();     // rotate motor to unlock
        delay(150);         // rotate duration (adjust to reach 90°)
        
        // Stop motor
        mp = 0;
        mn = 0;
        
        delay(1000);        // 4 seconds wait while unlocked
        delay(1000);
        //delay(1000);
        //delay(1000);
        
        // Lock again
        lockback();         // rotate reverse to lock
        //delay(400);         // same rotation time for locking
        
        // Stop motor again
        mp = 0;
        mn = 0;

        attempts = 0;
    }
    else
    {
        attempts++;
        lcd_cmd(0x01);
        printString("PASSWORD WRONG");
        lcd_cmd(0xC0);
        printString("TRY AGAIN");
        delay(800);

        if (attempts >= 3)
        {
            attempts = 0;
            wait();   // 10-sec lockout
        }
    }
}


// ====== Wait 10 seconds after 3 wrong attempts ======
void wait(void)
{
    unsigned char i;
    lcd_cmd(0x01);
    printString("ACCESS DENIED");
    lcd_cmd(0xC0);
    printString("WAIT 10 SECONDS");

    for (i = 10; i > 0; i--)
    {
        lcd_cmd(0xC0);
        printString("WAIT ");
        lcd_data((i / 10) + '0');
        lcd_data((i % 10) + '0');
        printString(" SECONDS ");
        delay(1000);
    }
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    printString("ENTER PASSWORD:");
    lcd_cmd(0xC0);
}

// ====== Change Password via Keypad ======
void change_password(void)
{
    unsigned char i, newkey;
    lcd_cmd(0x01);
    printString("SET NEW PASSWORD:");
    lcd_cmd(0xC0);

    for (i = 0; i < 4; i++)
    {
        newkey = keyscan();
        while (!(newkey >= '0' && newkey <= '9'))
            newkey = keyscan();

        password[i] = newkey;
        lcd_data('*');
    }

    lcd_cmd(0x01);
    printString("PASSWORD UPDATED");
    delay(800);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
    printString("ENTER PASSWORD:");
    lcd_cmd(0xC0);
}
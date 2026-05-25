#include <reg51.h>
sbit mp = P3^3;   
sbit mn = P3^4;   
void motor_init(void);
void motor_unlock(void);
void lockback(void);
void motor_init(void)
{
    mp = 0;
    mn = 0;
}
void motor_unlock(void)
{
    mp = 1;
    mn = 0;
	
}
void lockback(void)
{
		
    mp = 0;
    mn = 1;
    delay(150);
    mp = 0;
    mn = 0;
}


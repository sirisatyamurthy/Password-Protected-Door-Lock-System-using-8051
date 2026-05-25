#include <reg51.h>

sbit R1 = P1^0;
sbit R2 = P1^1;
sbit R3 = P1^2;
sbit R4 = P1^3;
sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;

char keyscan(void)
{
    while (1)
    {
        R1 = R2 = R3 = R4 = 0;
        C1 = C2 = C3 = 1;

        // Check if any key is pressed
        if (C1 == 0 || C2 == 0 || C3 == 0)
        {
            
            unsigned int i;
            for (i = 0; i < 5000; i++);

            
            R1 = 0; R2 = R3 = R4 = 1;
            if (C1 == 0) { while(C1==0); return '1'; }
            if (C2 == 0) { while(C2==0); return '2'; }
            if (C3 == 0) { while(C3==0); return '3'; }

            R2 = 0; R1 = R3 = R4 = 1;
            if (C1 == 0) { while(C1==0); return '4'; }
            if (C2 == 0) { while(C2==0); return '5'; }
            if (C3 == 0) { while(C3==0); return '6'; }

            R3 = 0; R1 = R2 = R4 = 1;
            if (C1 == 0) { while(C1==0); return '7'; }
            if (C2 == 0) { while(C2==0); return '8'; }
            if (C3 == 0) { while(C3==0); return '9'; }

            R4 = 0; R1 = R2 = R3 = 1;
            if (C1 == 0) { while(C1==0); return '*'; }
            if (C2 == 0) { while(C2==0); return '0'; }
            if (C3 == 0) { while(C3==0); return '#'; }
        }
    }
}

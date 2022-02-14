#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping
#include<stdint.h> // Declare sets of integer types having specified widths

uint8_t i, j;

// Variable Delay Function:
void delay_ms(uint16_t j)
{
    uint16_t x, i;

	// Loop to Generate 1 ms Delay with CCLK = 60 MHz:
	for(i=0;i<j;i++)
	{
    	for(x=0; x<6000; x++);
	}
}

// Main Function:
int main (void)
{
	IO0DIR = (IO0DIR | 0x0000000F);	// Configure P0.0-P0.3 as output, used for controlling stepper motor

	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		// Full Step Rotation in One Direction:
		for(i=0;i<12;i++)	
		{
			IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x0000000C) & 0xFFFFFFFC );
			delay_ms(100); // Call Delay Function
			
			IO0PIN = ( (IO0PIN | 0x00000004) & 0xFFFFFFF4 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x00000006) & 0xFFFFFFF6 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x00000002) & 0xFFFFFFF2 );
			delay_ms(100); // Call Delay Function
			
			IO0PIN = ( (IO0PIN | 0x00000003) & 0xFFFFFFF3 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x00000009) & 0xFFFFFFF9 );
			delay_ms(100); // Call Delay Function		
		}
		
		IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
		delay_ms(100); // Call Delay Function
		delay_ms(2000); // Call Delay Function

		// Half Step Rotation in Opposite Direction:
		for(j=0;j<12;j++)
		{
			IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x00000002) & 0xFFFFFFF2 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x00000004) & 0xFFFFFFF4 );
			delay_ms(100); // Call Delay Function
				
			IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
			delay_ms(100); // Call Delay Function
		}
		
		IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
		delay_ms(100); // Call Delay Function
		delay_ms(2000); // Call Delay Function
	}
}

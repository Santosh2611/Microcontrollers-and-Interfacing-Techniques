#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping

// Variable Delay Function:
int wait(unsigned int w)
{
	unsigned int a,b;
	for(a=0;a<w;a++)
	{
		for(b=0;b<200;b++);
	}
	return 0;
}

// Main Function:
int main()
{
	PINSEL0 = 0x00000000; // Configure functionality of Port0 as GPIO
   	IODIR0 = 0XFFFFFFFF; // Configure direction of Port0 as output

   	// Infinite Loop (An embedded program does not stop):
   	while(1)
   	{
		// Assume that the segments a, b, c, d, e, f, g, dp are connected to P0.7 to P0.0 respectively.

        IOPIN0 = 0XFC; // Value written to common anode to display '0'
		wait(5000); // Call Delay Function

		IOPIN0 = 0X60; // Value written to common anode to display '1'
		wait(5000); // Call Delay Function

		IOPIN0 = 0XDA; // Value written to common anode to display '2'
		wait(5000); // Call Delay Function
		
		IOPIN0 = 0XF2; // Value written to common anode to display '3'
		wait(5000); // Call Delay Function

		IOPIN0 = 0X66; // Value written to common anode to display '4'
		wait(5000); // Call Delay Function

		IOPIN0 = 0XB6; // Value written to common anode to display '5'
		wait(5000); // Call Delay Function

		IOPIN0 = 0XBE; // Value written to common anode to display '6'
		wait(5000); // Call Delay Function

		IOPIN0 = 0XE0; // Value written to common anode to display '7'
		wait(5000); // Call Delay Function

		IOPIN0 = 0XFE; // Value written to common anode to display '8'
		wait(5000); // Call Delay Function

		IOPIN0 = 0XF6; // Value written to common anode to display '9'
		wait(5000); // Call Delay Function	  	 
	}
}

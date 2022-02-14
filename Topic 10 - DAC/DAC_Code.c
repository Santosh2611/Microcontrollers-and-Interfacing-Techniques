#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping 

// Generate a triangular waveform using DAC:
int main (void)
{
	unsigned int value;
	PINSEL1 = 0x00080000; // Configure P0.25 as DAC pin (Aout)
	
	// Infinite Loop (An embedded program does not stop):
	while(1)
	{			
		value = 0;
		while ( value != 1023 )	// Increasing from 0 to 2^10 voltage level resolutions
		{
			DACR = ( (1<<16) | (value<<6) ); // Configure value of DAC output and set 16-bit BIAS as 1 
			value++;
		}	
		while ( value != 0 ) // Decreasing from 2^10 to 0 voltage level resolutions
		{
			DACR = ( (1<<16) | (value<<6) ); // Configure value of DAC output and set 16-bit BIAS as 1 
			value--;
		} 		
	}
}

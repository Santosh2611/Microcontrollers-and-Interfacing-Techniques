#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping  

// Variable Delay Function:
void wait(unsigned int w)
{
	unsigned int a,b;
	for(a=0;a<w;a++)
		for(b=0;b<200;b++);
}

// Main Function:
int main()
{
  PINSEL2 = 0x00000000; // Configure Functionality of P1.31 to P1.16 as GPIO Port
  IODIR1 = 0XFFFFFFFF; // Configure Direction of P1.31 to P1.16 as Output Port

  // Infinite Loop (An embedded program does not stop):
  while(1)
  {
  	IOSET1 = 0XFFFFFFFF; // Switch ON all LEDs on Port1 (Configure Data as Logic HIGH)
	wait(25000); // Delay = 25000 * 200 Execution Time
  	IOCLR1 = 0XFFFFFFFF; // Switch OFF all LEDs on Port1 (Configure Data as Logic LOW)
	wait(25000); // Delay = 25000 * 200 Execution Time
  }
}

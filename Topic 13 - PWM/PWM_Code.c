#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping   

// Main Function:
int main()
{
	PINSEL1 = 0x00000400; // Configure P0.21 as PWM5 pin
	PWMPCR = 0x00; // Configure Single Edge PWM mode
	PWMPR = 60000 - 1; // Configure resolution of PWM is set at 1 ms

	PWMMR0 = 10; // Configure period of PWM is 10 ms
	PWMMCR = (1<<1); // Configure Timer Counter (TC) to reset on match with PWMMR0
	PWMLER = (1<<5) | (1<<0); // Update match registers PWMMR0 with PWMMR5

	PWMPCR = (1<<13); // Enable PWM5 output
	PWMTCR = (1<<1); // Reset PWM TC and PWM PR
	PWMTCR = (1<<0) | (1<<3); // Enable PWM Timer Counter (TC) and PWM mode; Also, Counter Reset = 0

	PWMMR5 = 1; // Configure pulse width (duty cycle) of PWM5 as 1 ms
	PWMLER = (1<<5); // Update match register PWMMR5
	while(1); // Infinite Loop (An embedded program does not stop)
}

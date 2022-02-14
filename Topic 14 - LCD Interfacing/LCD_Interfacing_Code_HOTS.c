#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping
#include<stdio.h> // Declares functions that deal with standard I/O  

// Define macros for LCD:
#define LCD (0xff<<8)
#define RS (1<<16)
#define RW (1<<17)
#define EN (1<<18)

void delay(unsigned int time); // Variable Delay Function
void lcd_ini(void); // Function to Configure LCD
void lcd_print(char *str); // Character Masking
void lcd_cmd(unsigned char command); // Display Character Using LCD Command Write Function
void lcd_dat(unsigned int data); // Display Character Using Data Write Function

unsigned char flag = 0;
unsigned char alarm = 0;

void rtc_int(void)__irq
{
	ILR = 0X01;
	flag = 1;
	VICVectAddr = 0X00000000;
}

void init_rtc()
{
	CCR  = 0X03;
	CCR =  0X01;
	PREINT = 0x01C8; // For 15 MHz F-PCLK -> PREINT value
	PREFRAC = 0x61C0; // For 15MHz F-PCLK -> PREFRAC value
	ILR = 0X01;
	CIIR = 0X01;

	// Initialize Time = NULL:
	SEC = 0X00; HOUR = 0X00; MIN = 0X00;

	// Initialize Date = 21/11/2020:
	DOM = 21; MONTH = 11; YEAR = 2020;

	VICIntEnable = 0x00002000;
	VICVectCntl0 = 0x0000002D;
	VICVectAddr0 = (unsigned)rtc_int;
}

char year[5], month[3], day[3];

// Main Function:
int main (void)
{
	PINSEL0 = 0x00000000; // Configure functionality of P0.0 to P0.15 as GPIO Port
    IODIR0 = 0Xffffffff; // Configure direction of P0.0 to P0.15 as output port
	IO0CLR = 0x00000010; // Clear P0.4 LED
    lcd_ini(); // Call the LCD Function
    lcd_print("Digital Clock");
	delay(2000); // Call Delay Function
	lcd_cmd(0x01); // Clear LCD display; Also, clear DDRAM content
    init_rtc();

	// Infinite Loop (An embedded program does not stop):
	while(1)
	{
		if((YEAR == 2020) && (MONTH == 11) && (DOM == 21) && (HOUR == 0) && (MIN == 00) && SEC == 5)
		{
			IO0SET = 0x00000010; // Set LCD_RS = 1
		}
		
		else if((YEAR == 2020) && (MONTH == 11) && (DOM == 21) && (HOUR == 0) && (MIN == 00) && SEC == 10)
		{
			IO0CLR = 0x00000010; // Set LCD_RW = 0
		}
		
		if(flag)
		{
			lcd_cmd(0x80); // Set DDRAM address or cursor position on display to first line
			flag = 0;
			lcd_dat(HOUR/10 + '0');	lcd_dat(HOUR%10 + '0'); 
			lcd_dat(':') ;
			lcd_dat(MIN/10 + '0'); lcd_dat(MIN%10 + '0');
			lcd_dat(':') ;
			lcd_dat(SEC/10 + '0'); lcd_dat(SEC%10 + '0');

			lcd_cmd(0xC0); // Set DDRAM address or cursor position on display to second line 
			sprintf(day,"%d",DOM); lcd_print(day);
			lcd_dat('/') ;
			sprintf(month,"%d",MONTH); lcd_print(month);
			lcd_dat('/') ;
			sprintf(year,"%d",YEAR); lcd_print(year);
		}
	}
}

// Display Character Using LCD Command Write Function:
void lcd_cmd(unsigned char command)
{
	// Split MSB and LSB 4-Bits of LCD Command:
	IO0CLR |= (RS|RW|EN|LCD); IO0SET |= (command<<8);
    IO0CLR |= RS; IO0CLR |= RW;

	// Give LCD Enable Signal:
    IO0SET |= EN;
    delay(2); // Call Delay Function
    IO0CLR |= EN;
    delay(3); // Call Delay Function
}

// Display Character Using Data Write Function:  
void lcd_dat(unsigned int data)        
{
	// Split MSB and LSB 4-Bits of LCD Command:
	IO0CLR |= (RS|RW|EN|LCD); IO0SET |= (data<<8);
    IO0SET |= RS; IO0CLR |= RW;

	// Give LCD Enable Signal:
    IO0SET |= EN;
    delay(2); // Call Delay Function
    IO0CLR |= EN;
    delay(3); // Call Delay Function
}

// Function for Character Masking:
void lcd_print(char *str)
{
	while(*str!='\0') // It involves a text field that accepts any character, however, doesn't show the inputted character to the user. 
    {
		lcd_dat(*str); // Instead, it shows an asterisk.
        str++;
    }
}

// Function to Configure LCD:
void lcd_ini(void)
{
	delay(5); // Call Delay Function
    lcd_cmd(0X38); // Function Set: 8-bit, 2 Line, 5*7 Dots
    lcd_cmd(0X0C); // Display ON, Cursor OFF, Blink OFF
    lcd_cmd(0X06); // Set the Entry Mode (Cursor Increment, Display Shift OFF)
    lcd_cmd(0X01); // Clear LCD display; Also, clear DDRAM content
    delay(5); // Call Delay Function
    lcd_cmd(0X80); // Set DDRAM address or cursor position on display to first line
}

// Variable Delay Function:
void delay(unsigned int time)
{
	unsigned int t1,t2;
    for(t1=0;t1<time;t1++)
	{
		for(t2=0;t2<1275;t2++);
	}
}

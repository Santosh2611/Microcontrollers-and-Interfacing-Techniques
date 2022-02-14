#include<lpc214x.h> // To define all Special Function Registers (SFRs) - Address Mapping

// Define macros for LCD:
#define LCD (0xff<<8)
#define RS (1<<16)
#define RW (1<<17)
#define EN (1<<18)

// Define macros for Keypad (Column):
#define col1 (1<<16)
#define col2 (1<<17)
#define col3 (1<<18)
#define col4 (1<<19)

// Define macros for Keypad (Row):
#define row1 (1<<20)
#define row2 (1<<21)
#define row3 (1<<22)
#define row4 (1<<23)

void delay(unsigned int time); // Variable Delay Function
void lcd_ini(void); // Function to Configure LCD
void lcd_print(char *str); // Character Masking
void lcd_cmd(unsigned char command); // Display Character Using LCD Command Write Function
void lcd_dat(unsigned int data); // Display Character Using Data Write Function
unsigned char keypad (void); // Function to Configure Keypad
void keypad_delay(void); // Variable Delay Function for Keypad

// Main Function:
int main (void)
{
	PINSEL0 = 0x00000000; // Configure functionality of PORT0 as GPIO
    IODIR0 = 0Xffffffff; // Configure direction of PORT0 as output (LCD)

    PINSEL1 = 0x00000000; // Configure functionality of PORT1 as GPIO
    IODIR1 = 0x00f00000; // Configure direction of PORT0 as input (Keypad)
        
    lcd_ini(); // Function to Configure LCD
    lcd_print("Press any key");
    lcd_cmd(0xc0); // Set DDRAM address or cursor position on display to second line 

    // Infinite Loop (An embedded program does not stop):
	while(1)
    {
		lcd_dat(keypad()); // Function to Configure Keypad
		keypad_delay(); // Variable Delay Function for Keypad
    }
}

// Variable Delay Function for Keypad:
void keypad_delay(void)
{
	unsigned int t1,t2;
    for(t1=0;t1<300;t1++)                 
    {
		for(t2=0;t2<1275;t2++);
	}
}

// Function to Configure Keypad1;
unsigned char keypad (void)
{
	unsigned char key;
    IOCLR1 |= (row1|row2|row3|row4|col1|col2|col3|col4);
    
	while(1)
    {
    	IOCLR1 |= row1; // First Row
        IOSET1 |= (row2|row3|row4); // First Column
                
        if((IOPIN1&col1)==0) // First Row, First Column
        {
        	key = '7';
            keypad_delay(); // Call Keypad Delay Function
			return key; 
        }
        
		else if((IOPIN1&col2)==0) // First Row, Second Column
        {
        	key = '8';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col3)==0) // First Row, Third Column
        {
        	key = '9';
            keypad_delay(); // Call Keypad Delay Function
			return key; 
        }
                
		else if((IOPIN1&col4)==0) // First Row, Fourth Column
        {
        	key = '/';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }

		IOCLR1 |= row2; // Second Row
        IOSET1 |= (row1|row3|row4); // Second Column
                
        if((IOPIN1&col1)==0) // Second Row, First Column
        {
        	key = '4';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col2)==0) // Second Row, Second Column
        {
			key = '5'; 
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col3)==0) // Second Row, Third Column
        {
        	key = '6';
            keypad_delay();  // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col4)==0) // Second Row, Fourth Column
        {
        	key = '*';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
                
        IOCLR1 |= row3; // Third Row
        IOSET1 |= (row1|row2|row4); // Third Column

        if((IOPIN1&col1)==0) // Third Row, First Column
        {
        	key = '1';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col2)==0) // Third Row, Second Column
        {
        	key = '2';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col3)==0) // Third Row, Third Column
        {
        	key = '3';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col4)==0) // Third Row, Fourth Column
        {
        	key = '-';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
		        
        IOCLR1 |= row4; // Fourth Row
        IOSET1 |= (row1|row2|row3); // Fourth Column

        if((IOPIN1&col1)==0) // Fourth Row, First Column
        {
			lcd_cmd(0x01); // Clear LCD display; Also, clear DDRAM content
        	keypad_delay(); // Call Keypad Delay Function           
        }
        
		else if((IOPIN1&col2)==0) // Fourth Row, Second Column
        {
        	key = '0';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col3)==0) // Fourth Row, Third Column
        {
        	key = '=';
            keypad_delay(); // Call Keypad Delay Function
			return key;
        }
        
		else if((IOPIN1&col4)==0) // Fourth Row, Fourth Column
        {
        	key = '+';
            keypad_delay(); // Call Keypad Delay Function
			return key; 
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
    lcd_cmd(0X0f); // Display ON, Cursor Blinking
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

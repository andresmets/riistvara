#include <8051.h>

signed int count = 250; // available space in the ParkHouse
unsigned char dvalues[10]; // array of values of display
unsigned char i; // variable used in indexing and delay
unsigned char number; // variable of diplay_value function
unsigned char p0; //value of count segment (ones)
unsigned char p1; // ---,,--- (tens)
unsigned char p2; // ---,,--- (hundreds)

// delay - ca 8,16 microsec if i = 1;
void button_delay(unsigned char i)
{
	unsigned char bd = 0;
	for (bd=0; bd < i; bd++){}
}
// value table for decimal display
display_values(unsigned char i)
{
	dvalues[0] = 192; //0
	dvalues[1] = 249; //1
	dvalues[2] = 164; //2
	dvalues[3] = 176; //3
	dvalues[4] = 153; //4
	dvalues[5] = 146; //5
	dvalues[6] = 130; //6
	dvalues[7] = 248; //7
	dvalues[8] = 128; //8
	dvalues[9] = 144; //9

	number = dvalues[i];
	return number;
}
//function for displaying numbers on mux LED
void show_display(unsigned char p0,unsigned char p1,unsigned char p2)
{
	P3_1 = 0;
	P2 = display_values(p0);
	P2 = 255;
	P3_1 = 1;

	P3_2 = 0;
	P2 = display_values(p1);
	P2 = 255;
	P3_2 = 1;

	P3_3 = 0;
	P2 = display_values(p2);
	P2 = 255;
	P3_3 = 1;
}
// funtion for calculating members of display
calc_numbers(signed int dv)
{
	if (dv > 99)
	{
		p2 = dv / 100;
		p1 = (dv % 100) / 10;
		p0 = (dv % 100) % 10;
	}
	else if (dv < 100)
	{
		button_delay(70);
		p1 = dv/10;
		p0 = dv%10;
	}
	else if(dv < 10)
	{
		button_delay(140);
		p0 = dv;
		p1 = p2 = 0;
	}
	return p0, p1, p2;
}
// check whether the car has driven out
void carout_check()
{
	while(P1_7 == 0)
	{
	button_delay(80); // simulates eliminating overflow in case of the car stopping in front of the sensor
	show_display(p0,p1,p2);

		if (P1_7 == 1)
		{
		count++;
		calc_numbers(count);
		}
	}
}
// check, if the car has entered
void carin_check()
{
	while (P1_6 == 0)
	{
	button_delay(80);
	show_display(p0,p1,p2);

		if (P1_6 == 1)
		{
		count--;
		calc_numbers(count);
		}
	}
}
// main program
void main()
{
    	calc_numbers(count);

while(1)
{
	if(count > 250) {show_display(0,5,2);} // shows max free parking spots, even if counter has reached over the 250(motorcycles or small cars shared a spot?)
	else if(count < 0) {show_display(0,0,0);} //shows min free parking spots even if there are more cars in the house than free spots - counter doesn't stop
    	else show_display(p0,p1,p2);
    	carin_check();
	carout_check();
}
}
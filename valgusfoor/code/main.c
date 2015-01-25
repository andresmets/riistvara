#include <8051.h>

// Pattern definitions
unsigned char pat_length = 24;

// Car ligths patterns
unsigned char C_red[] = { 32, 48, 48, 48, 48, 16, 80, 80, 80, 80, 208, 192, 192, 192, 192, 192, 0, 12, 12, 12, 12, 12, 12, 0 };
unsigned char C_yellow[] = { 220, 476, 252, 252, 220, 252, 188, 252, 252, 236, 108, 252, 252, 252, 252, 60, 252, 240, 252, 252, 252, 252, 240, 252 };
unsigned char C_green[] = { 252, 220, 204, 204, 236, 236, 236, 172, 172, 188, 188, 60, 60, 60, 60, 252, 252, 252, 240, 240, 240, 240, 252, 252 };

// Pedestrian lights patterns
unsigned char P_red[] = { 80, 80, 84, 4, 4, 4, 4, 12, 8, 8, 8, 8, 40, 168, 160, 160, 160, 160, 224, 240, 112, 80, 80, 80};
unsigned char P_green_P0[] = { 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2};
unsigned char P_green_P1[] = { 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2};
unsigned char P_green_P2[] = { 3, 3, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

// Delay patterns
unsigned char delay_pattern[] = { 1, 1, 2, 4, 3, 3, 1, 16, 3, 2, 1, 3, 3, 6, 3, 3, 1, 1, 1, 24, 2, 2, 3, 1 };

unsigned char timeCounter = 0;
unsigned char indexCounter = 0;

void timer_1us(void) __interrupt 1 {
  TL0 = 156;
  TH0 = 255;

  timeCounter++;

  if (delay_pattern[indexCounter] == timeCounter) {
    timeCounter = 0;
    indexCounter++;
    if (indexCounter >= pat_length) {
    	indexCounter = 0;
    }
  }
}

void main(void) {

	ET0 = 1;
	EA = 1;
	TMOD = 0x01;
	TL0 = 156;
	TH0 = 255;
	TR0 = 1;
	
	while (1) {
		P0 = C_red[indexCounter] & P_green_P0[indexCounter];
		P1 = C_yellow[indexCounter] & P_green_P1[indexCounter];
		P2 = C_green[indexCounter] & P_green_P2[indexCounter];

		P3 = P_red[indexCounter];
	}

}
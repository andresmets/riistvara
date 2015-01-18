#import <8051.h>

// returns numbers from 0-7 for keys or 8 for no selection
unsigned char readFromKeyboard() {
  P0 = 255;

  if (P0_0 == 0) {
    return 0;
  }
  else if (P0_1 == 0) {
    return 1;
  }
  else if (P0_2 == 0) {
    return 2;
  }
  else if (P0_3 == 0) {
    return 3;
  }
  else if (P0_4 == 0) {
    return 4;
  }
  else if (P0_5 == 0) {
    return 5;
  }
  else if (P0_6 == 0) {
    return 6;
  }
  else if (P0_7 == 0) {
    return 7;
  }

  return 8;
}

// Shows the number or display or . if no selection
void displayNum(unsigned char num) {
  if (num == 8) {
    P1 = 127;
    return;
  }

  switch(num) {
    case 0:
      P1 = 192;
      break;
    case 1:
      P1 = 249;
      break;
    case 2:
      P1 = 164;
      break;
    case 3:
      P1 = 176;
      break;
    case 4:
      P1 = 153;
      break;
    case 5:
      P1 = 146;
      break;
    case 6:
      P1 = 130;
      break;
    case 7:
      P1 = 248;
      break;
    case 8:
      P1 = 128;
      break;
    case 9:
      P1 = 144;
      break;
  }
}

void main() {
  unsigned char num;
  while(1) {
    num = readFromKeyboard();
    displayNum(num);
  }
}
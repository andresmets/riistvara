#include <8051.h>

#define LCD_DATA P0
#define LCD_BUSY P0_7
#define LCD_RS P1_2 // Selects register
#define LCD_RW P1_1 // selects read/write
#define LCD_EN P1_0 // starts data read/write
#define PUMP_SWITCH P1_3 // A led light is used to signify the pump output
#define TANK_DQ P2_0
#define TANK_CLK P2_1
#define TANK_RST P2_2
#define PANEL_DQ P3_0
#define PANEL_CLK P3_1
#define PANEL_RST P3_2

unsigned char tank_sign = 0;
unsigned char tank_temp = 0;
unsigned char panel_sign = 0;
unsigned char panel_temp = 0;

unsigned char numMap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
void lcdBusy() {
  LCD_EN = 1; LCD_EN = 0;
  LCD_BUSY = 1;
  LCD_EN = 1;
  LCD_RS = 0;
  LCD_RW = 1;
  while (LCD_BUSY) {
    LCD_EN = 0; LCD_EN = 1;
  }
}

void sendCommand(unsigned char cmd) {
  LCD_DATA = cmd;
  LCD_RS = 0; //command
  LCD_RW = 0;
  lcdBusy();
}

void sendChar(unsigned char var) {
  LCD_DATA = var;
  LCD_RS = 1; //data
  LCD_RW = 0;
  lcdBusy();
}

void updateDisplay() {
  unsigned char part;

  sendCommand(0x80);

  // Update Tank temp
  sendChar('T');sendChar(':');

  if (tank_sign == 255) {
    sendChar('-');
  }
  else {
    sendChar(' ');
  }

  part = tank_temp / 100;
  if (part > 0) {
    sendChar(numMap[part]);
  }
  else {
    sendChar(' ');
  }
  part = (tank_temp % 100) / 10;
  if (part > 0) {
    sendChar(numMap[part]);
  }
  else {
    sendChar(' ');
  }
  part = tank_temp % 10;
  sendChar(numMap[part]);

  sendChar(' ');sendChar('|');sendChar(' ');
  // Update panel temp
  sendChar('P');sendChar(':');

  if (panel_sign == 255) {
    sendChar('-');
  }
  else {
    sendChar(' ');
  }

  part = panel_temp / 100;
  if (part > 0) {
    sendChar(numMap[part]);
  }
  else {
    sendChar(' ');
  }
  part = (panel_temp % 100) / 10;
  if (part > 0 || panel_temp / 100 > 0) {
    sendChar(numMap[part]);
  }
  else {
    sendChar(' ');
  }
  part = panel_temp % 10;
  sendChar(numMap[part]);
}

void TANK_send(unsigned char command) {
    unsigned char i, b = 1;
    TANK_RST = 1;
    for (i = 0; i < 8; i++) {
        TANK_CLK = 0;
        TANK_DQ = command & b;
        TANK_CLK = 1;
        b = ( b << 1 );
    }
}
void PANEL_send(unsigned char command) {
    unsigned char i, b = 1;
    PANEL_RST = 1;
    for (i = 0; i < 8; i++) {
        PANEL_CLK = 0;
        PANEL_DQ = command & b;
        PANEL_CLK = 1;
        b = ( b << 1 );
    }
}

unsigned char TANK_read() {
  unsigned char i, b = 1;        // bit counters
  unsigned char tmp = 0;        // readed data byte

  for (i = 0; i < 8; i++) {
    TANK_CLK = 0;        // toggle clock
    if (TANK_DQ) {
      tmp = tmp | b;    // get bit readed (if not zero)
    }
    TANK_CLK = 1;        // toggle clock
    b = ( b << 1 );        // shift to next bit
  }
  return tmp;
}

signed char PANEL_read() {
  unsigned char i, b = 1;        // bit counters
  unsigned char tmp = 0;        // readed data byte

  for (i = 0; i < 8; i++) {
    PANEL_CLK = 0;        // toggle clock
    if (PANEL_DQ) {
      tmp = tmp | b;    // get bit readed (if not zero)
    }
    PANEL_CLK = 1;        // toggle clock
    b = ( b << 1 );        // shift to next bit
  }
  return tmp;
}

void readTankTemp() {
  unsigned char status = 0;
  TANK_RST = 1;
  TANK_send(0xEE); // Start measure
  TANK_RST = 0;

  do {
    TANK_RST = 1;
    TANK_send(0xAC); // Read status
    status = TANK_read();
    TANK_RST = 0;
  } while ((status & 0x80) != 0x80);

  TANK_RST = 1;
  TANK_send(0xAA);    // command to read temperature
  tank_temp = TANK_read();
  tank_sign = TANK_read();
  TANK_RST = 0;

  if (tank_sign == 255) {
    tank_temp = 128 - (tank_temp >> 1);
  }
  else {
    tank_temp = tank_temp >> 1;
  }
}
void readPanelTemp() {
  unsigned char status = 0;
  PANEL_RST = 1;
  PANEL_send(0xEE); // Start measure
  PANEL_RST = 0;

  /*do {
    PANEL_RST = 1;
    PANEL_send(0xAC); // Read status
    status = PANEL_read();
    PANEL_RST = 0;
  } while ((status & 0x80) != 0x80);*/

  PANEL_RST = 1;
  PANEL_send(0xAA);    // command to read temperature
  panel_temp = PANEL_read();
  panel_sign = PANEL_read();
  PANEL_RST = 0;

  if (panel_sign == 255) {
    panel_temp = 128 - (panel_temp >> 1);
  }
  else {
    panel_temp = panel_temp >> 1;
  }
}

void main(void) {

  PUMP_SWITCH = 1; // 0 is ON, 1 is OFF
  
  sendCommand(0x38); // Function Set: 8-bit, 2 Line, 5x7 Dots
  sendCommand(0x0C); // Display on Cursor off 
  // 0x0F cursor on
  sendCommand(0x01); // Clear LCD
  sendCommand(0x06); // Entry mode

  while(1) {
    readTankTemp();
    readPanelTemp();

    if (panel_sign != 255 && panel_sign != 255) { // Check if both temp are positive
      if (panel_temp > 40 && panel_temp >= tank_temp) {
        PUMP_SWITCH = 0; // 0 is ON, 1 is OFF
      }
      else {
        PUMP_SWITCH = 1;
      }
    }
    else {
      PUMP_SWITCH = 1;
    }

    // read panel temp

    
    // read tank temp
    // toggle tank switch if needed

    updateDisplay();
  }
}
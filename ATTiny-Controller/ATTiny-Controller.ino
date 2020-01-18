#include "PID_v1.h"
#include "SSD1306_minimal.h"
#include <avr/pgmspace.h>

//DISPLAY------------------------------------------------------------------------------------------------------------------
SSD1306_Mini oled;

//Byte array of bitmap of 123 x 48 px:
const unsigned char solder_logo [] PROGMEM = {
  0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0xc3, 0x83, 0x00, 0x00, 0xfc, 0xfe, 0x07, 0x03, 0x03, 0x07, 0xfe, 0xfc, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x07, 0xfe, 0xfc, 0x00, 0x00, 0xff, 0xff, 0x63, 0x63, 0x63, 0x03, 0x03, 0x00, 0x00, 0xff, 0xff, 0xe3, 0xe3, 0xe3, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x03, 0x03, 0xff, 0xff, 0x03, 0x03, 0x00, 0x00, 0xff, 0xff, 0x0c, 0x18, 0x30, 0x60, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xfe, 0x07, 0x03, 0xc3, 0xc3, 0xce, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf8, 0x78, 0x38, 0x0c, 0x0c, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x78, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x03, 0x07, 0x0e, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x0f, 0x0f, 0x0c, 0x0c, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x03, 0x07, 0x0e, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0xc3, 0x83, 0x00, 0x00, 0x03, 0x03, 0x03, 0xff, 0xff, 0x03, 0x03, 0x03, 0x00, 0x00, 0xf8, 0xfe, 0x87, 0x83, 0x83, 0x87, 0xfe, 0xf8, 0x00, 0x00, 0x03, 0x03, 0x03, 0xff, 0xff, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0xff, 0xff, 0x03, 0x03, 0x00, 0x00, 0xfc, 0xfe, 0x07, 0x03, 0x03, 0x07, 0xfe, 0xfc, 0x00, 0x00, 0xff, 0xff, 0x0c, 0x18, 0x30, 0x60, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x01, 0x01, 0x01, 0x01, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0f, 0x0f, 0x0c, 0x0c, 0x00, 0x00, 0x03, 0x07, 0x0e, 0x0c, 0x0c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0xb8, 0x5c, 0x2e, 0x17, 0x0b, 0x07, 0x07, 0x0f, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0xb8, 0x5c, 0x2e, 0x17, 0x0b, 0x05, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 0x07, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

char buff[20];

//PWM----------------------------------------------------------------------------------------------------------------------
#define PWM_pin 1
int level;

//ADC----------------------------------------------------------------------------------------------------------------------
#define SETPOINT_MUL 1
#define SETPOINT_ADD 230

#define INPUT_MUL 1
#define INPUT_ADD 230

#define ADC_CMD_pin A2
#define ADC_TEMP_pin A3
int temp_return;

//PID----------------------------------------------------------------------------------------------------------------------
//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
  
void logo()
{

  oled.startScreen();
  oled.clear();

  oled.drawImage(solder_logo, 5, 2, 123, 6);  //immagine, x, y, n° byte x, n° colonne byte
  delay(2000);
}

void initDISPLAY()
{
  oled.init(0x3c); //indirizzo del display
  oled.clear();

  delay(1000);
  
  logo();

  oled.clear();
}


void initPID()
{
  //initialize the variables we're linked to
  Setpoint = SETPOINT_ADD + SETPOINT_MUL * (analogRead(ADC_CMD_pin) >> 2); //10bit to 8bit
  Input = INPUT_ADD + INPUT_MUL * (analogRead(ADC_TEMP_pin) >> 2); //10bit to 8bit

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void writePID()
{
  Input = INPUT_ADD + INPUT_MUL * (analogRead(ADC_TEMP_pin) >> 2); //10bit to 8bit

  double gap = abs(Setpoint-Input); //distance away from setpoint
  if (gap < 10)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
  }

  myPID.Compute();
  analogWrite(PWM_pin, Output);
}

void setup() 
{
  pinMode(PWM_pin, OUTPUT);
  
  initPID();
  initDISPLAY();
}

void loop() 
{  
  Setpoint = SETPOINT_ADD + SETPOINT_MUL * (analogRead(ADC_CMD_pin) >> 2); //10bit to 8bit
  
//limiti di temperatura
  if (Setpoint < 250) Setpoint = 250;
  if (Setpoint > 450) Setpoint = 450;

  writePID();

  sprintf(buff, "Setpoint: %d     ", int(Setpoint));
  oled.cursorTo(5, 2);
  oled.printString(buff, 0, 5, 2);

  sprintf(buff, "Input: %d     ", int(Input));
  oled.cursorTo(5, 3);
  oled.printString(buff, 0, 5, 2);

  sprintf(buff, "Output: %d     ", int(Output));
  oled.cursorTo(5, 4);
  oled.printString(buff, 0, 5, 2);
}

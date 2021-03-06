#include "SSD1306_minimal.h"
#include <avr/pgmspace.h>
#include <avr/wdt.h>
  
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
/*
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf8, 0x78, 0x38, 0x0c, 0x0c, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x78, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x70, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0xb8, 0x5c, 0x2e, 0x17, 0x0b, 0x07, 0x07, 0x0f, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06,
  0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0xb8, 0x5c, 0x2e, 0x17, 0x0b, 0x05, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x06, 0x07, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
*/
};

char buff[20];
unsigned long last_time;
int print_setpoint, print_input, print_output;
#define REFRESH_TIME_MS 150 

//PWM----------------------------------------------------------------------------------------------------------------------
#define PWM_pin 1

//ADC----------------------------------------------------------------------------------------------------------------------
//Formula retta per scalatura lettura temperatura
//Y = mX + q
//    X  -  Y
//1. 460 - 151
//2. 760 - 495
//m = dy / dx = 1.148
//q = (x2y1 - x1y2) / (x2 - x1) = -377.526
float INPUT_MUL = 11.48;
int INPUT_ADD = -3770;

//Formula retta per scalatura temperatura di comando
//Y = mX + q
//    X  -  Y
//1.  23 - 200
//2.1000 - 450
//m = dy / dx = 0.2559
//q = (x2y1 - x1y2) / (x2 - x1) = 194.1146
float SETPOINT_MUL = 2.559;
int SETPOINT_ADD = 1940;

#define ADC_CMD_pin A2
#define ADC_TEMP_pin A3

//PID----------------------------------------------------------------------------------------------------------------------
#define TEMPERATURE_GAP 300

float Upper_Total_limit = 255;
float Lower_Total_limit = 0;

float Kp = 0.5;
float Ki = 0.001;
float Kd = 0.3;

float P = 0; /* componente proporzionale */
float I = 0; /* componente integrale */
float D = 0; /* componente differenziale */

int old_error = 0; /*differenza tra valore di consegna e valore reale @ z-1 */

int Setpoint, Input, Output;

//FUNCTIONS----------------------------------------------------------------------------------------------------------------
void initDISPLAY()
{
  delay(1000);
  oled.init(0x3c); //indirizzo del display
  oled.startScreen();
  oled.clear();

  oled.drawImage(solder_logo, 5, 2, 123, 6);  //immagine, x, y, n° byte x, n° colonne byte
//  oled.drawImage(solder_logo, 62, 2, 61, 6);  //immagine, x, y, n° byte x, n° colonne byte
  delay(1500);

  oled.clear();
}

//SETUP--------------------------------------------------------------------------------------------------------------------
void setup() 
{
  MCUSR = 0x00; //resetta il registro di stato della MCU
  wdt_disable();
  
  pinMode(PWM_pin, OUTPUT);
  
  initDISPLAY();
  initINTERRUPT();

  last_time = millis();

  wdt_enable(WDTO_1S);
  sei(); //enable interrupts
}

//MAIN---------------------------------------------------------------------------------------------------------------------
void loop() 
{
  Setpoint = int(SETPOINT_MUL * analogRead(ADC_CMD_pin)) + SETPOINT_ADD;
//limiti di temperatura
  if (Setpoint < 2000) Setpoint = 2000;
  if (Setpoint > 4500) Setpoint = 4500;
  Setpoint = (Setpoint / 50) * 50;

  Input = int(INPUT_MUL * analogRead(ADC_TEMP_pin)) + INPUT_ADD;

  print_setpoint = Setpoint / 10;
  print_input = (Input / 50) * 5;
  if (Input % 50 >= 25)
    print_input += 5;
  
//stampo parametri ogni "REFRESH_TIME_MS"
  if (millis() - last_time >= REFRESH_TIME_MS) 
  { 
    sprintf(buff, "Setpoint: %3d  ", print_setpoint);
    oled.cursorTo(5, 1);
    oled.printString(buff);
  
    sprintf(buff, "Input: %3d  ", print_input);
    oled.cursorTo(5, 2);
    oled.printString(buff);
  
    sprintf(buff, "Output: %3d  ", print_output);
    oled.cursorTo(5, 3);
    oled.printString(buff);

    int temp_kp = int(P);
    int temp_ki = int(I);
    int temp_kd = int(D);
    sprintf(buff, "P:%5d I:%5d", temp_kp, temp_ki);
    oled.cursorTo(5, 4);
    oled.printString(buff);

    sprintf(buff, "D:%5d", temp_kd);
    oled.cursorTo(5, 5);
    oled.printString(buff);
    
    last_time = millis();
  }
  
  wdt_reset();
}

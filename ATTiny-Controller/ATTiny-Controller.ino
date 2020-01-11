
#include "SSD1306_minimal.h"
#include <avr/pgmspace.h>

//DISPLAY-----------------------------------------------------------------------------------------------------------------
SSD1306_Mini oled;
//Byte array of bitmap of 76 x 56 px:
const unsigned char img_logo [] PROGMEM = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x30, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x07, 0xc3, 0xe3, 0xe3, 0xe3, 0xe3, 0xc3, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xe1, 0xc3, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xff, 0xff, 0xff, 0xf0, 0xe0, 0xe3, 0xc7, 0xc7, 0xc7, 0xc7, 0xe3, 0xe0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0x03, 0x7f, 0x7f, 0x7f, 0x7f, 0x03, 0xe3, 0x03, 0x7f, 0x7f, 0x7f, 0x03, 0xe3, 0x03, 0x7f, 0x7f, 0x7f, 0x7f, 0x03, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x0f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x0f, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x8f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x8f, 0x8f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xc0, 0xc0, 0xf0, 0xff, 0xff, 0xf9, 0xf1, 0x01, 0x01, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf1, 0x01, 0x01, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x01, 0x03, 0xe3, 0xf1, 0xf1, 0xf1, 0xf1, 0x01, 0x03, 0xff, 0xff, 0xff, 0xff, 0x07, 0x03, 0xe1, 0xf1, 0xf1, 0xf1, 0xf1, 0xe1, 0x03, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe0, 0xe0, 0xe0, 0xe3, 0xe3, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xe3, 0xe0, 0xe0, 0xe0, 0xe3, 0xe3, 0xf7, 0xff, 0xff, 0xf0, 0xe0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf0, 0xf1, 0xe3, 0xe3, 0xe3, 0xe3, 0xf1, 0xf0, 0xf8, 0xff, 0xff, 0xff, 0xff
};

//PWM----------------------------------------------------------------------------------------------------------------------
int PWM_pin = 1;
int level;
  
void splash()
{

  oled.startScreen();
  oled.clear();
  
  oled.drawImage( img_logo, 20,0, 76, 7 );  
  delay(2000);
}

void setup() 
{
  pinMode(PWM_pin, OUTPUT);
  
  oled.init(0x3c);
  oled.clear();

  delay(1000);
  
  splash();

  oled.clear();
}

void loop() 
{
  for(int i = 0; i < 100; i++)
  {
    analogWrite(PWM_pin, i);
    delay(50);
  }
}
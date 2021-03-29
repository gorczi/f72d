#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino

#include <Arduino.h>
#include <U8g2lib.h>

#define ONE_WIRE_BUS 10

OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const uint8_t *font = u8g2_font_crox3cb_tf;
byte digitWidth = 13;
byte digitHeight = 20;

float tempC;
float tempC_tmp;
int num = 123;
byte xOffset = 0;


void setup(void) {
  u8g2.begin();
  sensors.begin();
}

void loop(void) {
  sensors.requestTemperatures(); // Send the command to get temperatures
  tempC = sensors.getTempCByIndex(0);
  printOLED_tmp();
}


void printOLED_tmp(void) {
  u8g2.setFont(font);  // choose a suitable font
  u8g2.firstPage();
  do {
    xOffset = 0;
    if ((tempC > -10 && tempC < 0)  || tempC >= 10)                //offset 1 chars
    {
      xOffset = digitWidth;
    }
    else if (tempC >= 0 &&  tempC < 10)                   //offset 2 chars
    {
      xOffset = digitWidth * 2;
    }

    u8g2.setCursor (0 + xOffset, 20);
    u8g2.print (tempC, 1);
    u8g2.drawGlyph(65, 20, 0x00b0); // degree
    u8g2.drawStr(75, 20, "C");
    u8g2.setCursor(83, 60);
    u8g2.print(xOffset);
} while ( u8g2.nextPage() );    
  delay(1000);
}

void printOLED(void) {
  u8g2.firstPage();
  do {
    u8g2.setFont(font);
    u8g2.setCursor(0, 20);
    u8g2.print(tempC, 1);
    u8g2.drawGlyph(53, 20, 0x00b0); // degree
    u8g2.drawStr(63, 20, "C");

    u8g2.setCursor(20, 40);
    u8g2.print(tempC, 1);
    u8g2.drawGlyph(73, 40, 0x00b0); // degree
    u8g2.drawStr(83, 40, "C");

    u8g2.setCursor(0, 60);
    u8g2.print(tempC, 1);
    u8g2.drawStr(53, 60, "V");
  } while ( u8g2.nextPage() );
  delay(1000);
}

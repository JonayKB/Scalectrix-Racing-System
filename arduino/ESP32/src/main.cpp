#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Arduino.h> // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include <U8g2_for_Adafruit_GFX.h>

Adafruit_FT6206 ctp = Adafruit_FT6206();

//------------------------------
// Set the legs of the TFT screen.
#define TFT_DC 15
#define TFT_CS 5
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define BOXSIZE 40

const int ledCount = 10;

int ledPins[] = {
    1, 2, 42, 41, 40, 35, 0, 45, 48, 47};

U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

void setup()
{

  Serial.begin(9600);
  Serial.println("Hello Arduino\n");

  for (int thisLed = 0; thisLed < ledCount; thisLed++)
  {
    pinMode(ledPins[thisLed], OUTPUT);
  }

  tft.begin();

  if (!ctp.begin(40))
  {
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1)
      ;
  }
  tft.setRotation(1);           // Set the rotation of the TFT display
  tft.fillScreen(ILI9341_BLACK); // Clear the screen with black color
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);    // Set text size
  tft.setCursor(10, 10); // Set cursor position
  tft.println("Touch the screen");
  tft.setCursor(10, 30); // Set cursor position
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(1); // Set text size
  tft.println("FT6206 Touchscreen Example");
  tft.setCursor(10, 50); // Set cursor position
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(1); // Set text size
  tft.println("Press the screen to draw");

  Serial.println("READY");
}
void Touch()
{
  if (!ctp.touched())
  {
    return;
  }

  TS_Point p = ctp.getPoint();

  // Ajustar coordenadas para rotación 1 (pantalla girada 90°)
  int x = map(p.y, 0, 320, 240, 0); // usar p.y para X
  int y = map(p.x, 0, 320, 0, 240); // usar p.x para Y

  Serial.print("Touch at: (");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.println(")");

  tft.fillRect(x - 5, y - 5, 10, 10, ILI9341_GREEN);
}


void loop()
{

  Touch();
  Serial.println("Loop running");
  for (int i = 0; i <= 9; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
}

#include "LedControl.h"

LedControl lc = LedControl(12, 10, 11, 2); // Pins: DIN,CLK,CS, # of Display connected

unsigned long delayTime = 100; // Delay between Frames


void setup()
{
  Serial.begin(9600);
  pinMode(8, INPUT);// set pin as input
  lc.shutdown(0, false); // Wake up displays
  lc.shutdown(1, false);
  lc.setIntensity(0, 5); // Set intensity levels
  lc.setIntensity(1, 5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
}

byte empty[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte eyesOpen[] = {
  B00000000,
  B01000010,
  B10100101,
  B01000010,
  B00000000,
  B01111110,
  B01000010,
  B00111100
};

byte eyesClosed[] = {
  B00000000,
  B00000000,
  B11100111,
  B00000000,
  B00000000,
  B01111110,
  B01000010,
  B00111100
};

void displayLoop(byte matrix[])
{
  for (int k = 0; k < 8; k++)
  {
    lc.setRow(0, k, matrix[k]);
    lc.setRow(1, k, matrix[k]);
  }
}





void loop()
{
  int detect = digitalRead(8);// read obstacle status and store it into "detect"
  if (detect != LOW) {
    displayLoop(eyesOpen);
  } else {
    displayLoop(eyesClosed);
  }
}

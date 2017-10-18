#include "ESP8266WiFi.h"

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<=16; i++){
    if (i == 7 || i == 8 || i == 9 || i == 10 || i == 11)
      continue;
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

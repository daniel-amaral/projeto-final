#include "ESP8266WiFi.h"

#define N_SAMPLES 10

void setup() {
  Serial.begin(9600);
}

void loop() {
  float voltage = readAverageVoltage();
  Serial.print(voltage);
  Serial.println(" V");
  float heliumLevel = voltage * 100;
  Serial.print("Helium level: ");
  Serial.print(heliumLevel);
  Serial.println("%");
  delay(5000);
}

float readAverageVoltage(){
  const float maxVoltageValue = 3.3;
  float sum = 0;
  for (int i=0; i<N_SAMPLES; i++){
    sum += analogRead(A0);
    delay(50);
  }
  float averageSensorValue = (float)(sum / N_SAMPLES);
  float voltage = averageSensorValue * (maxVoltageValue / 1023.0);
  return voltage;
}


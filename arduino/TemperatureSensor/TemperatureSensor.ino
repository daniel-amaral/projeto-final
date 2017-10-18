#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempSensor;

void setup() {
  Serial.begin(9600); 
  initSensor();
}

void loop() {
  float temperature = getTemperatureFromSensor();
  Serial.println("temperature: " + String(temperature));
  delay(6000);
}

void initSensor(){
  sensors.begin();
  sensors.getDeviceCount();
  sensors.getAddress(tempSensor, 0);
  if (!sensors.getAddress(tempSensor, 0)) 
     Serial.println("Sensores nao encontrados !");
  else
    Serial.println("Sensores encontrados !");
}

float getTemperatureFromSensor(){
  //sensors.requestTemperatures();
  //return sensors.getTempC(tempSensor);
  return sensors.getTempCByIndex(0);
}

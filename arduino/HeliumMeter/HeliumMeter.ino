#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include <OneWire.h>
#include <DallasTemperature.h>

char ssid[] = "casa - NET";     // network SSID (name) 
char pass[] = "familia100";     // network password
int status = WL_IDLE_STATUS;    // the Wifi radio's status
HTTPClient http;                // used send a HTTP POST

#define BUZZER_PIN 13
#define RELAY_1_PIN 0
#define TEMP_PIN 16
#define MAX_VOLTAGE_VALUE 3.3 // arduino board caracteristic
#define N_SAMPLES 5           // samples to make average value

OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress tempSensor;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  initPins();
  initSensor();
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
 // attempt to connect to Wifi network:
  while ( WiFi.status() != WL_CONNECTED) {  // WL_CONNECTED === 3
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("Succesfully connected! :)");  
  printCurrentNet();
  printWifiData();
}

void initPins(){
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_1_PIN, OUTPUT);
}

void loop() {
  turnOnRelay1();
  buzzer(250, 500);
  float heliumLevel = readHeliumLevel();
  float temperature = getTemperatureFromSensor();
  Serial.print("temperature: " + String(temperature));
  postHeliumInfo(heliumLevel);
  buzzer(100, 200);
  buzzer(100, 0);
  turnOffRelay1();
  delay(8 * 1000);
  /*
  // check the network connection once every 10 seconds:
  delay(10000);
  printCurrentNet();
  */
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  
  // print your MAC address:
  byte mac[6];  
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

    // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
}

void postHeliumInfo(float heliumLevel) {
  Serial.println("Initializing POST...");
  
  String serverIp = "192.168.1.25";
  String serverPort = "3000";
  String serverEndpoint = "/sample-post";
  String sampleData = "{\"machine\":\"arduino-sample\",\"heliumLevel\":" + String(heliumLevel, 2) + "}";
  String url = "http://" + serverIp + ":" + serverPort + serverEndpoint;

  Serial.println("URL: " + url);
    
  http.begin(url);  
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(sampleData);
  String payload = http.getString();

  Serial.println("Response Code: " + httpResponseCode);
  Serial.println(payload + "\n");
}

float readHeliumLevel(){
  float sum = 0;
  for (int i=0; i<N_SAMPLES; i++){
    sum += analogRead(A0);
    delay(50);
  }
  float averageSensorValue = (float)(sum / N_SAMPLES);
  float voltage = averageSensorValue * (MAX_VOLTAGE_VALUE / 1023.0);
  return voltage * 100;
}

void initSensor(){
  sensors.getDeviceCount();
}

float getTemperatureFromSensor(){
  return sensors.getTempC(tempSensor);
}

void buzzer(int duration, int delayAfter){
  Serial.println("buuuuzzerrr...");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
  delay(delayAfter);
}

void turnOnRelay1(){
  digitalWrite(RELAY_1_PIN, HIGH);
}

void turnOffRelay1(){
  digitalWrite(RELAY_1_PIN, LOW);
}




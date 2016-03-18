#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define DHTTYPE DHT11

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include "DHT.h"

SimpleTimer timer;
// Token generated by Blynk app
char auth[] = "b8b23b4bf63642c79ed9e5fa510415c1"; 

// PINS
int RELAY = 12;
int LIGHT = 14;
int DHT_PIN = 16;

// Initialize DHT sensor.
DHT dht(DHT_PIN, DHTTYPE);

void sendDHT() {
  //Read the Temp and Humidity from DHT
  int t = (int) dht.readTemperature();
  int h = (int) dht.readHumidity();
 
  Blynk.virtualWrite(1, t);
  Blynk.virtualWrite(2, h);
  
}

void setup() {
  Serial.begin(115200);

  Serial.println("*** ESP8266 Remote Control Fimware ***");
  Serial.println("%\t Begin Connection...%\n");

  timer.setInterval(2000, sendDHT);
  dht.begin();
  
  Blynk.begin(auth, "Telecom-52227471", "biagiobotticelliaureliacasalini");
  
  pinMode(RELAY, OUTPUT);
  pinMode(LIGHT,OUTPUT);
}

void loop() {
  digitalWrite(LIGHT, HIGH);
  Blynk.run();
  timer.run();
}
#include "DHT.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Variaveis
// Sensores
int luminosity;
float humidity;
float temperature;
int soloHumidity;
SoftwareSerial esp(3, 2);

// Atuadores
bool pump;
bool automatic;
bool cooler;

// String para comunicação NODEMCU esp8266
String str;

// Pinos
const int pinDHT11 = A1;
const int pinHumidity = A2;
const int pinPump = 4;
const int pinCooler = 3;

DHT dht(pinDHT11, DHT11);

void setup() {
  pinMode(pinHumidity, INPUT);
  pinMode(pinCooler, OUTPUT);
  pinMode(pinPump, OUTPUT);

  StaticJsonDocument<99> doc;
  
  automatic = false;
  cooler = false;
  pump = false;
  dht.begin();
  
  Serial.begin(9600);
  esp.begin(4800);
}

void loop() {

  if (esp.available()) {
    DeserializationError error = deserializeJson(doc, esp.read());
    if (error) {
      Serial.println("Parsing failed!");
      return;
    }
  } else {
    automatic = doc["automatic"];
    pump = doc["pump"];
    cooler = doc["cooler"];
  }

  
  soloHumidity = analogRead(pinHumidity);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  str = "{";
  str += "\"soloHumidity\": " + String(soloHumidity);
  str += ", \"humidity\": " + String(humidity);
  str += ", \"temperature\": " + String(temperature);
  str += ", \"pump\": " + String(pump);
  str += ", \"cooler\": " + String(cooler);
  str += ", \"auto\": " + String(automatic);
  str += "}";

  if (automatic) {
    if (soloHumidity > 450) {
      digitalWrite(pinPump, !true);
    } else {
      digitalWrite(pinPump, !false);
    }
    if (temperature > 30) {
      digitalWrite(pinCooler, !true);
    } else {
      digitalWrite(pinCooler, !false);
    }    
  } else {
    digitalWrite(pinPump, !pump);
    digitalWrite(pinCooler, !cooler);
  }

  
  Serial.println("------------------------------"); 

  // Enviar dados NodeMCU ESP8266

  Serial.print(str);
//  Arduino.print(str); 
  delay(1000);
}

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

//StaticJsonDocument<99> doc;

// Pinos
const int pinDHT11 = A1;
const int pinHumidity = A2;
const int pinPump = 3;
const int pinCooler = 4;


DHT dht(pinDHT11, DHT11);

void setup() {
  pinMode(pinHumidity, INPUT);
  pinMode(pinCooler, OUTPUT);
  pinMode(pinPump, OUTPUT);

  automatic = true;
  cooler = false;
  pump = false;
  dht.begin();

  Serial.begin(9600);
  esp.begin(4800);
}


void loop() {

//  DeserializationError error = deserializeJson(doc, str);

  //  if (Serial.available()) {
  //    DeserializationError error = deserializeJson(doc, esp.read());
  //    if (error) {
  //      Serial.println("Parsing failed!");
  //      return;
  //    }
  //  } else {
  //    automatic = doc["automatic"];
  //    pump = doc["pump"];
  //    cooler = doc["cooler"];
  //  }


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

  Serial.println(str);
  
  int str_len = str.length() + 1;

  char json[str_len];

  str.toCharArray(json, str_len);

  Serial.println(json);
  
  StaticJsonDocument<200> doc;
  deserializeJson(doc, json);
  const double world = doc["soloHumidity"];
  Serial.println(world, 6);

  if (automatic) {
    if (soloHumidity > 450) {
      digitalWrite(pinPump, !true);
    } else {
      digitalWrite(pinPump, !false);
    }
    if (temperature > 33) {
      digitalWrite(pinCooler, !true);
    } else {
      digitalWrite(pinCooler, !false);
    }
  } else {
    digitalWrite(pinCooler, !pump);
    digitalWrite(pinPump, !cooler);
  }


  Serial.println("------------------------------");

  // Enviar dados NodeMCU ESP8266

//  Serial.print(str);
  //  Arduino.print(str);
  delay(1000);
}

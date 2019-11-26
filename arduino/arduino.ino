#include "DHT.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Variaveis
// Sensores
int luminosity;
float humidity;
float temperature;
int soloHumidity;
SoftwareSerial Nodemcu(10, 11);

// Atuadores
bool pump;
bool automatic;
bool cooler;

// String para comunicação NODEMCU esp8266
String str;
String data;

// JSON
StaticJsonDocument<200> doc;


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

  automatic = 1;
  cooler = 0;
  pump = 0;
  dht.begin();

  Serial.begin(9600);
  Nodemcu.begin(9600);
}


void loop() {
  
  if (Nodemcu.available() > 0) {
    data = Nodemcu.readString();
    int data_len = data.length() + 1;
    char json[data_len];
    data.toCharArray(json, data_len);

    DeserializationError error = deserializeJson(doc, json);
    if (error) {
      Serial.println("Parsing failed!");
      return;
    } else {
      automatic = doc["automatic"];
      pump = doc["pump"];
      cooler = doc["cooler"];
    }
  }

  soloHumidity = analogRead(pinHumidity);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (automatic) {
    if (soloHumidity > 450) {
      pump = 1;
    } else {
      pump = 0;
    }
    if (temperature > 33) {
      cooler = 1;
    } else {
      cooler = 0;
    }
  }

  str = "{";
  str += "\"soloHumidity\": " + String(soloHumidity);
  str += ", \"humidity\": " + String(humidity);
  str += ", \"temperature\": " + String(temperature);
  str += ", \"pump\": " + String(pump);
  str += ", \"cooler\": " + String(cooler);
  str += ", \"automatic\": " + String(automatic);
  str += "}";
  
  digitalWrite(pinPump, !pump);
  digitalWrite(pinCooler, !cooler);

  // Enviar dados NodeMCU ESP8266
  Nodemcu.println(str);
  Serial.println(str);
  delay(1000);
}

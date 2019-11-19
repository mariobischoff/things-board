//#include "DHT.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Variaveis
// Sensores
int luminosity;
float humidity;
float temperature;
int soloHumidity;
SoftwareSerial Nodemcu(5, 6);

// Atuadores
bool pump;
bool automatic;
bool cooler;

// String para comunicação NODEMCU esp8266
String str;
String data;

StaticJsonDocument<99> doc;

// Pinos
const int pinDHT11 = A1;
const int pinHumidity = A2;
const int pinPump = 3;
const int pinCooler = 4;


//DHT dht(pinDHT11, DHT11);

void setup() {
  pinMode(pinHumidity, INPUT);
  pinMode(pinCooler, OUTPUT);
  pinMode(pinPump, OUTPUT);

  automatic = true;
  cooler = false;
  pump = false;
//  dht.begin();

  Serial.begin(9600);
  Nodemcu.begin(9600);
}


void loop() {

  if (Nodemcu.available()) {
    data = Nodemcu.readString();
    Serial.println(data);
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
//  humidity = dht.readHumidity();
//  temperature = dht.readTemperature();

  str = "{";
  str += "\"soloHumidity\": " + String(soloHumidity);
//  str += ", \"humidity\": " + String(humidity);
//  str += ", \"temperature\": " + String(temperature);
  str += ", \"pump\": " + String(pump);
  str += ", \"cooler\": " + String(cooler);
  str += ", \"automatic\": " + String(automatic);
  str += "}";

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
  Nodemcu.print(str);
  str = "";
  delay(3000);
}

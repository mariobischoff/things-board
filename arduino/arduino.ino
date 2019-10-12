#include "DHT.h"
// #include <SoftwareSerial.h>


// SoftwareSerial Arduino(3, 2);


// Variaveis
// Sensores
int luminosity;
float humidity;
float temperature;
int soloHumidity;

// Atuadores
bool pump;
bool lamp;
bool cooler;

// String para comunicação NODEMCU esp8266
String str;

// Pinos
const int pinDHT11 = A1;
const int pinHumidity = A2;
const int pinLamp = 3;
const int pinPump = 3;
const int pinCooler = 4;

DHT dht(pinDHT11, DHT11);

void setup() {
  pinMode(pinHumidity, INPUT);
  pinMode(pinLamp, OUTPUT);
  pinMode(pinCooler, OUTPUT);

  dht.begin();
  Serial.begin(9600);
//  Arduino.begin(4800);
}

void loop() {
  
  soloHumidity = analogRead(pinHumidity);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  Serial.print("solo humidity: ");
  Serial.println(soloHumidity);

  Serial.print("temperature: ");
  Serial.println(temperature);

  Serial.print("humidity: ");
  Serial.println(humidity);

  Serial.println("------------------------------");

  pump = true;
  cooler = false;
  digitalWrite(pinPump, !pump);
  digitalWrite(pinCooler, !cooler);

//  if (soloHumidity < 400) {
//   digitalWrite(pinCooler, LOW);
//   digitalWrite(pinPump, HIGH); 
//  } else {
//    digitalWrite(pinCooler, HIGH);
//    digitalWrite(pinPump, LOW);
//  }
  

  // Enviar dados NodeMCU ESP8266
  str = String(soloHumidity);
  str += ";" + String(temperature);
  str += ";" + String(humidity);

//  Serial.print(str);
//  Arduino.print(str);
  delay(1000);
}

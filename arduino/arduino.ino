#include "DHT.h"
#include <SoftwareSerial.h>


SoftwareSerial Arduino(3, 2);



// Variaveis
// Sensores
int luminosity;
int soloHumidity;
int temperature;

// Atuadores
bool pump;
bool lamp;
bool cooler;

String str;

const int pinLDR = A0;
const int pinHumidity = A1;
const int pinDHT11 = A2;
const int pinPump = 2;
const int pinLamp = 3;
const int pinCooler = 4;

DHT dht(pinDHT11, DHT11);

void setup() {
  pinMode(pinoLDR, INPUT);
  pinMode(pinoHumidity, INPUT);

  dht.begin();
  Serial.begin(9600);
  Arduino.begin(4800);


}

void loop() {
  dht.read11(pinDHT11);
  luminosity = analogRead(pinoLDR);
  soloHumidity = analogRead(pinoHumidity);

  Serial.print("luminosity: ");
  Serial.println(luminosity);

  Serial.print("solo humidity: ");
  Serial.println(soloHumidity);

  Serial.print("temperature: ");
  Serial.print(dht.temperature);

  Serial.print("humidity: ");
  Serial.print(dht.humidity);



  // Enviar dados NodeMCU ESP8266
  str = String(luminosity);
  str += String(humidity);
  Arduino.print(str);
  delay(5000);
}

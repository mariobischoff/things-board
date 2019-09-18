#include <SoftwareSerial.h>

SoftwareSerial Arduino(3, 2);
int luminosity;
int humidity;
String str;
const int pinoLDR = A0;
const int pinoHumidity = A1;

void setup() {
  pinMode(pinoLDR, INPUT);
  pinMode(pinoHumidity, INPUT);
  Serial.begin(9600);
  Arduino.begin(4800);
  Serial.println("Goodnight moon!");
}

void loop() {
  luminosity = analogRead(pinoLDR);
  humidity = analogRead(pinoHumidity);
  
  Serial.print("luminosity: ");
  Serial.println(luminosity);
  
  Serial.print("humidity: ");
  Serial.println(humidity);
  
  str = String(luminosity);
  str += String(humidity);
  Arduino.print(str);
  delay(5000);
}

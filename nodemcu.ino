#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

// Define o pino para comportar como serial
SoftwareSerial Nodemcu(D2, D3);

// Variavel que sera utilizada para armazenar os valores a ser enviado
String data;

// SSID e Password da rede WiFi
const char* SSID = "Bischoff";
const char* PASSWORD = "Kryptos12";

 
void setup() 
{
  // Inicia Serial
  Serial.begin(9600);
  Nodemcu.begin(4800);

  // Configura o pino do Serial
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);

  // Inicia WiFi
  WiFi.begin(SSID, PASSWORD);
}
 
void loop() 
{
  // Entra quando tiver dados na Serial e o WiFi estiver conectado
  if (Nodemcu.available() > 0 && (WiFi.status() == WL_CONNECTED)) {
    
    data = "{\"luminosity\": ";
    data += Nodemcu.readString();
    data += "}";
    Serial.println(data);
    
    HTTPClient http;
    http.begin("http://192.168.0.109:3000/thing");
    http.addHeader("Content-Type", "application/json");

    http.POST(data);
    http.end();
    data = "";
  }
  delay(2500);
}

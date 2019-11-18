#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
#include <SoftwareSerial.h>

WiFiClient client;
SocketIoClient webSocket;

// SSID e Password da rede WiFi
const char* ssid = "Bischoff";
const char* password = "Kryptos12";

SoftwareSerial Arduino(12, 14);
String data;


void setConfig(const char * payload, size_t length) {
  Serial.printf(payload);
  Arduino.print(payload);
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Arduino.begin(9600);
  
    // Inicia WiFi
  WiFi.begin(ssid, password);

  // Conectando na Rede
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
  webSocket.on("setConfig", setConfig);
  webSocket.begin("192.168.0.109", 3000, "/socket.io/?transport=websocket");
}


void loop() {
  webSocket.loop();
  if (Arduino.available() > 0 && (WiFi.status() == WL_CONNECTED)) {
    data = Arduino.readString();
    int data_len = data.length() + 1;
    char char_array[data_len];
    data.toCharArray(char_array, data_len);
    webSocket.emit("sendData", char_array);
  }
}

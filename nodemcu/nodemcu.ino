#include <SocketIoClient.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WebSocketClient.h>
//#include <SoftwareSerial.h>

char* count;
boolean auth = 0;
char* email = "mariobischoffneto@hotmail.com";
char* pw = "123123";

boolean handshakeFailed = 0;
char path[] = "/board/5dc7276011c6d139c8bbcb0d/";
char* host = "192.168.0.109";
const int espport = 3000;

//WebSocketClient webSocketClient;
SocketIoClient webSocket;
WiFiClient client;

// Define o pino para comportar como serial
//SoftwareSerial Nodemcu(D2, D3);

// Variavel que sera utilizada para armazenar os valores a ser enviado
String data;

// SSID e Password da rede WiFi
const char* ssid = "Bischoff";
const char* password = "Kryptos12";

void setConfig(const char * payload, size_t length) {
  Serial.printf("got config: %s\n", payload);
}

// Conecta no servidor WS
//void wsconnect(){
//  if (client.connect(host, espport)) {
//    Serial.println("Connected.");
//  } else {
//    Serial.println("Connection failed.");
//    delay(1000);
//    if (handshakeFailed) {
//      handshakeFailed = 0;
//      ESP.restart();
//    }
//    handshakeFailed = 1;
//  }
//  webSocketClient.path = path;
//  webSocketClient.host = host;
//  if (webSocketClient.handshake(client)) {
//    Serial.println("Handshake successful.");
//  } else {
//    Serial.println("Handshake failed.");
//    delay(4000);
//    if (handshakeFailed) {
//      handshakeFailed = 0;
//      ESP.restart();
//    }
//    handshakeFailed = 1;
//  }
//}
 
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  // Inicia Serial
  Serial.begin(9600);
//  Nodemcu.begin(4800);

  // Configura o pino do Serial
//  pinMode(D2, INPUT);
//  pinMode(D3, OUTPUT);

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
//  wsconnect();
}
 
void loop() 
{
  webSocket.loop();
  delay(2000);
  webSocket.emit("data", "{\"sensor1\": 20,\"button1\": true}");
  
  // Entra quando tiver dados na Serial e o WiFi estiver conectado
//  if (Nodemcu.available() > 0 && (WiFi.status() == WL_CONNECTED)) {
//    
//    data = "{\"luminosity\": ";
//    data += Nodemcu.readString();
//    data += "}";
//    Serial.println(data);
//    
//    HTTPClient http;
//    http.begin("http://192.168.0.109:3000/thing");
//    http.addHeader("Content-Type", "application/json");
//
//    http.POST(data);
//    http.end();
//    data = "";
//  }
//  delay(2500);

//  webSocketClient.getData(data);
//  if (data.length() > 0) {
//    Serial.println(data);
//  }
  
//  digitalWrite(LED_BUILTIN, !HIGH);
//  delay(500);
//  digitalWrite(LED_BUILTIN, !LOW);
//  webSocketClient.sendData("{\"sensor1\": 20,\"button1\": true}");

//  delay(5000);
}

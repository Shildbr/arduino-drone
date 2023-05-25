#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D4, D3); // RX, TX
const char* ssid = "NodeMCU_AP";
const char* password = "password";
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from the NodeMCU AP!");
}

void handlePost() {
if (server.method() == HTTP_POST) {
    String body = server.arg("plain");

    // Extrair o conteúdo entre as aspas
    int firstQuoteIndex = body.indexOf('"');
    int lastQuoteIndex = body.lastIndexOf('"');
    String value = body.substring(firstQuoteIndex + 9, lastQuoteIndex);

    Serial.print("Dados recebidos: ");
    Serial.println(value);
    mySerial.print(value);
    mySerial.print("/");
    server.send(200, "text/plain", "Requisição POST recebida com sucesso!");
  }
}

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);

  // Configura o NodeMCU como Access Point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Endereço IP do AP: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.on("/post", handlePost);
  server.begin();
}

void loop() {
  server.handleClient();
}
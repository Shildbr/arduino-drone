#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Definindo o nome e a senha do ponto de acesso
const char* ssid = "NodeMCU";
const char* password = "123456789";

// Inicializando o servidor web na porta 80
ESP8266WebServer server(80);

void setup() {
  // Inicializando o modo de acesso point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  // Imprimindo o endereço IP do Access Point
  IPAddress IP = WiFi.softAPIP();
  Serial.begin(115200);
  Serial.println();
  Serial.print("Endereço IP do Access Point: ");
  Serial.println(IP);

  // Manipuladores de rotas
  server.on("/", [] (){
    server.send(200, "cabeçalho", "Bem Vindo Ao Servidor Do NodeMCU");      
      });
  server.on("/offred", [] (){
      server.send(200, "cabeçalho", "Led Vermelha apagada");      
      });
  // Iniciando o servidor web
  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  // Lidando com as solicitações do servidor web
  server.handleClient();
}

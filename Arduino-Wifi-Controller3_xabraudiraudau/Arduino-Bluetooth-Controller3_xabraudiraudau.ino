#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(D3, D4); // RX, TX
const char* ssid = "ZTE_F14_2.4G";
const char* password = "10943104";
const int webSocketPort = 80;
 
WiFiServer server(webSocketPort);
WebSocketsServer webSocketServer = WebSocketsServer(webSocketPort);
 
void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectado!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocketServer.remoteIP(num);
        Serial.printf("[%u] Conectado do IP %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
    case WStype_TEXT:
      {
        String receivedMessage;
        receivedMessage.reserve(length);  // Reserve memory for the string
        receivedMessage = String((char*)payload);  // Convert the payload to a string
 
        // Verifique se a mensagem recebida pode ser convertida em um número inteiro
        if (receivedMessage.toInt() != 0 || receivedMessage == "0") {
          Serial.printf("%s\n", receivedMessage.c_str());
          delay(10);
          mySerial.printf("%s\n", receivedMessage.c_str());
 
          // Envie uma resposta de volta para o cliente com a mensagem original
          String responseMessage = receivedMessage;
          webSocketServer.sendTXT(num, responseMessage);
        }
      }
      break;
  }
}
 
void setup() {
  Serial.begin(38400);
  mySerial.begin(38400);
 
  // Conectar-se à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
 
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
 
  // Inicializar o servidor WebSocket
  webSocketServer.begin();
  webSocketServer.onEvent(webSocketEvent);
}
 
void loop() {
  // Aguarde uma nova conexão do cliente
  webSocketServer.loop();
 
  // Verifique se há dados disponíveis no dispositivo serial
  while (mySerial.available()) {
    int receivedByte = mySerial.read();
    Serial.write(receivedByte); // Exibe o byte recebido no monitor serial
  }
}
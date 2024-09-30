#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "RIFFEL 2.4GHZ";
const char* password = "#Juliana@2020+";
const int webSocketPort = 80;
float inputReceived;

WebSocketsServer webSocketServer(webSocketPort);

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
        receivedMessage.reserve(length);
        receivedMessage = String((char*)payload);

        if (receivedMessage.toInt() != 0 || receivedMessage == "0") {
          Serial.printf("%s\n", receivedMessage.c_str());
          inputReceived = receivedMessage.toFloat();
          String responseMessage = receivedMessage;
          webSocketServer.sendTXT(num, responseMessage);  
        }
      }
      break;
  }
}

void setupWebSocket() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

  webSocketServer.begin();
  webSocketServer.onEvent(webSocketEvent);
}

void loopWebSocket() {
  webSocketServer.loop();
}

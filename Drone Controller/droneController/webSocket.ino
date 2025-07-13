#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>  // <- Adicionada biblioteca

const char* ssid = "RIFFEL 2.4GHZ";
const char* password = "#Juliana@2020+";
const int webSocketPort = 80;

float inputReceived;
float kp, ki, kd;

WebSocketsServer webSocketServer(webSocketPort);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectado!\n", num);
      break;

    case WStype_CONNECTED: {
      IPAddress ip = webSocketServer.remoteIP(num);
      Serial.printf("[%u] Conectado do IP %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      break;
    }

    case WStype_TEXT: {
      StaticJsonDocument<200> doc;

      DeserializationError error = deserializeJson(doc, payload, length);
      if (error) {
        Serial.print("Erro ao parsear JSON: ");
        Serial.println(error.c_str());
        return;
      }

      // Espera um array com 4 valores: [position, kp, ki, kd]
      if (doc.is<JsonArray>() && doc.size() == 4) {
        inputReceived = doc[0];
        kp = doc[1];
        ki = doc[2];
        kd = doc[3];
/*
        // Debug
        Serial.println("Dados recebidos:");
        Serial.printf("Posição: %.2f", inputReceived);
        Serial.printf(" | Kp: %.2f", kp);
        Serial.printf(" | Ki: %.2f", ki);
        Serial.printf(" | Kd: %.2f\n", kd);
        */
      } else {
        Serial.println("Formato JSON inválido ou tamanho incorreto");
      }

      break;
    }
  }
}

void setupWebSocket() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  webSocketServer.begin();
  webSocketServer.onEvent(webSocketEvent);
}

void loopWebSocket() {
  webSocketServer.loop();
}

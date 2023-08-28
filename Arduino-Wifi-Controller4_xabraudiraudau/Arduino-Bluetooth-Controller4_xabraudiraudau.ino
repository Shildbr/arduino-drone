#include <SoftwareSerial.h>
#include <Servo.h>

#include <stdlib.h>
#define motor 6

Servo esc;
float velocidade;

SoftwareSerial mySerial(12, 13);  // RX, TX

void setup() {
  Serial.begin(38400);
  mySerial.begin(38400);
  pinMode(motor, OUTPUT);
  esc.attach(motor);
  esc.writeMicroseconds(1000);  // Velocidade mínima
  delay(1000);
  esc.writeMicroseconds(2000);  // Velocidade máxima
  delay(1000);
}

void loop() {
  if (mySerial.available()) {
    char message[20];  // Tamanho máximo da string recebida

    // Ler a string recebida
    mySerial.readBytesUntil('\n', message, sizeof(message));

    // Converter a string em um número inteiro
    int valor = atoi(message);

    // Ajustar o valor para o intervalo desejado (0 a 200)
    if (valor < 1) {
      valor = 0;
    } else if (valor > 100) {
      valor = 100;
    }

    // Converter o valor para a faixa de velocidade desejada
    int velocidade = map(valor, 0, 50, 1000, 2000);

    Serial.println(velocidade);
    esc.writeMicroseconds(velocidade);
  }
}

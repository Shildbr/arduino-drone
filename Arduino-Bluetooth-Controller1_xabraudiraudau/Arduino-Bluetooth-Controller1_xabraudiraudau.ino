#include <SoftwareSerial.h>

SoftwareSerial serialPort(10, 11);  // RX, TX

#define motor 6
float velocidade;
float setPower;

void setup() {
  // put your setup code here, to run once:
  serialPort.begin(9600);
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
}

void loop() {

  // put your main code here, to run repeatedly:
  if (serialPort.available()) {
    byte byteRecebido = serialPort.read();
    if (byteRecebido == '1') {
      setPower = 100;
    }
    if (byteRecebido == '2') {
      setPower = 50;
    }
    if (byteRecebido == '3') {
      setPower = 25;
    }
    if (byteRecebido == '4') {
      setPower = 0;
    }


    velocidade = setPower / 100 * 255;
    analogWrite(motor, velocidade);

    Serial.print("Velocidade: ");
    Serial.print(velocidade);
    Serial.print("\t");
    Serial.print("Power: ");
    Serial.print(setPower);
    Serial.print("\t");
  }
}

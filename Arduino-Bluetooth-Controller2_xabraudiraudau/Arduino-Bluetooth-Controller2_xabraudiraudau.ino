#include <SoftwareSerial.h>
#include <Servo.h>
#define motor 6

Servo esc;

float velocidade;

SoftwareSerial mySerial(12, 13); // RX, TX

void setup() {
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  esc.attach(motor);
  esc.writeMicroseconds(1000);  // Velocidade mínima
  delay(1000);
  esc.writeMicroseconds(2000);  // Velocidade máxima
  delay(1000);
}

void loop() {
    if (mySerial.available()) {
    Serial.write(mySerial.read());
  }


  velocidade = joystick_1_y/2/ 100 * 1000 + 1000;

  Serial.println(velocidade);
  esc.writeMicroseconds(velocidade);
}
#include <Wire.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include "MPU6050_tockn.h"

// Variáveis globais
extern void PIDcontrole();
extern void setupWebSocket();
extern void loopWebSocket();
extern float PID_X;
extern float PID_Y;
extern float PID_Z;
extern float inputReceived;
extern float kp, ki, kd;

float input;
float outputMotor_left_front;
float outputMotor_right_front;
float outputMotor_left_rear;
float outputMotor_right_rear;

#define Esc1 D8
#define Esc2 D2
#define Esc3 D7
#define Esc4 D1

Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  int SDA = D6;
  int SCL = D5;
  Wire.begin(SDA, SCL);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  esc1.attach(Esc1);
  esc2.attach(Esc2);
  esc3.attach(Esc3);
  esc4.attach(Esc4);

  esc1.writeMicroseconds(2000);
  esc2.writeMicroseconds(2000);
  esc3.writeMicroseconds(2000);
  esc4.writeMicroseconds(2000);

  delay(2000);

  esc1.writeMicroseconds(1000);
  esc2.writeMicroseconds(1000);
  esc3.writeMicroseconds(1000);
  esc4.writeMicroseconds(1000);

  delay(1000);

  PIDcontrole();
  setupWebSocket();
}

void loop() {

  input = map(inputReceived, 0, 200, 1000, 2000);

  outputMotor_left_front = input - PID_X + PID_Y ;
  outputMotor_right_front = input - PID_X - PID_Y;
  outputMotor_left_rear = input - PID_X - PID_Y;
  outputMotor_right_rear = input + PID_X - PID_Y;

  outputMotor_left_front = constrain(outputMotor_left_front, 1000, 2000);
  outputMotor_right_front = constrain(outputMotor_right_front, 1000, 2000);
  outputMotor_left_rear = constrain(outputMotor_left_rear, 1000, 2000);
  outputMotor_right_rear = constrain(outputMotor_right_rear, 1000, 2000);

  esc1.writeMicroseconds(outputMotor_left_front);
  esc2.writeMicroseconds(outputMotor_right_front);
  esc3.writeMicroseconds(outputMotor_left_rear);
  esc4.writeMicroseconds(outputMotor_right_rear);

  Serial.print("Motor 1 ");
  Serial.print(outputMotor_right_rear);
  Serial.print(" | Motor 2 ");
  Serial.print(outputMotor_right_front);
  Serial.print(" | KP ");
  Serial.print(kp);
  Serial.print(" | KI ");
  Serial.print(ki);
  Serial.print(" | KD ");
  Serial.print(kd);
  Serial.print(" PID X ");
  Serial.println(PID_X);

  PIDcontrole();
  loopWebSocket();
}

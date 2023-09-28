#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>

#define Esc1 6
#define Esc2 7

Servo esc1;
Servo esc2;

float input = 1300;

float Kp = 2.4;
float Ki = 0.003;
float Kd = 1.65;

float calcP, calcI, calcD;

float desiredAngle = 0;

float angleX, angleY, angleZ;

float outputMotor1, outputMotor2;

float PID, error, previousError, time, previousTime,
elapsedTime;

MPU6050 mpu6050(Wire);

void setup() {
  // put your setup code here, to run once:

  Wire.begin();
  Serial.begin(250000);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false);
  
  esc1.attach(Esc1);
  esc2.attach(Esc2);

  esc1.writeMicroseconds(1000);
  esc2.writeMicroseconds(1000);
  delay(3000);

  time = millis();

}

void loop() {
  // put your main code here, to run repeatedly:

  mpu6050.update();

  angleX = mpu6050.getAngleX();
  angleY = mpu6050.getAngleY();
  angleZ = mpu6050.getAngleZ();

  error = angleX - desiredAngle;

  previousTime = time; 
  time = millis();
  elapsedTime = (time - previousTime) / 1000;
  
  calcP = Kp*error;

  if (-3<error <3) {
    calcI = calcI + (Ki*error);
  }

  calcD = Kd*((error - previousError)/elapsedTime);

  PID = calcP + calcI + calcD;

  outputMotor1 = input - PID;
  outputMotor2 = input + PID;

  esc1.writeMicroseconds(outputMotor1);
  esc2.writeMicroseconds(outputMotor2);

  Serial.print(error);
  Serial.print(" ");
  Serial.println(PID);

  previousError = error;

}


#include <Wire.h>
#include <WebSocketsServer.h>
#include <MPU6050_tockn.h>

extern void setupWebSocket();
extern void loopWebSocket();

extern float kp, ki, kd;
float currentTime, elapsedTime, previousTime;

float PID_X, angleX, errorX, previousErrorX;
float PID_Y, angleY, errorY, previousErrorY;
float PID_Z, angleZ, errorZ, previousErrorZ;

float Kp_X = 0; //2.4
float Ki_X = 0; //0.003
float Kd_X = 0; //3.65

float Kp_Y = 2;
float Ki_Y = 0;
float Kd_Y = 0;

float Kp_Z = 2;
float Ki_Z = 0;
float Kd_Z = 0;

float calcP_X, calcI_X, calcD_X;
float calcP_Y, calcI_Y, calcD_Y;
float calcP_Z, calcI_Z, calcD_Z;

float desiredAngle = 0;

void PIDcontrole() {

  mpu6050.update();

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0;

  angleX = mpu6050.getAngleX();
  angleY = mpu6050.getAngleY();
  angleZ = mpu6050.getAngleZ();

  errorX = angleX - desiredAngle;
  errorY = angleY - desiredAngle;
  errorZ = angleZ - desiredAngle;

  Kp_X = kp; //2.4
  Ki_X = ki; //0.003
  Kd_X = kd; //3.65
//########### PID_PITCH ###########

// Cálculo do termo proporcional (P)
calcP_X = Kp_X * errorX;

// Cálculo do termo integral (I)
if (-3 < errorX && errorX < 3) {
  calcI_X += Ki_X * errorX;
}

// Cálculo do termo derivativo (D)
calcD_X = Kd_X * ((errorX - previousErrorX) / elapsedTime);

// Soma dos termos para obter o valor final do PID
PID_X = calcP_X + calcI_X + calcD_X;

// Limitando o valor do PID entre -1000 e 1000
PID_X = constrain(PID_X, -1000, 1000);
//########### PID_ROW ###########

// Cálculo do termo proporcional (P)
calcP_Y = Kp_Y * errorY;

// Cálculo do termo integral (I)
if (-3 < errorY && errorY < 3) {
  calcI_Y += Ki_Y * errorY;
}

// Cálculo do termo derivativo (D)
calcD_Y = Kd_Y * ((errorY - previousErrorY) / elapsedTime);

// Soma dos termos para obter o valor final do PID
PID_Y = calcP_Y + calcI_Y + calcD_Y;

// Limitando o valor do PID entre -1000 e 1000
PID_Y = constrain(PID_Y, -1000, 1000);
//########### PID_YAW ###########

// Cálculo do termo proporcional (P)
calcP_Z = Kp_Z * errorZ;

// Cálculo do termo integral (I)
if (-3 < errorZ && errorZ < 3) {
  calcI_Z += Ki_Z * errorZ;
}

// Cálculo do termo derivativo (D)
calcD_Z = Kd_Z * ((errorZ - previousErrorZ) / elapsedTime);

// Soma dos termos para obter o valor final do PID
PID_Z = calcP_Z + calcI_Z + calcD_Z;

// Limitando o valor do PID entre -1000 e 1000
PID_Z = constrain(PID_Z, -1000, 1000);
/*
  Serial.print("PID_X: ");
  Serial.println(angleX);
  Serial.print(" | ");
  Serial.print("PID_Y: ");
  Serial.print(angleY);
  Serial.print(" | ");
  Serial.print("PID_Z: ");
  Serial.print(angleZ);

Serial.printf(" | Kp: %.2f", kp);
Serial.printf(" | Ki: %.2f", ki);
Serial.printf(" | Kd: %.2f\n", kd);
*/
  previousErrorX = errorX;
  previousErrorY = errorY;
  previousErrorZ = errorZ;

}

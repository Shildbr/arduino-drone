#include <MPU6050_tockn.h>

float time, elapsedTime, previousTime;
float PID, error, previousError;
float angleX, angleY, angleZ;

float Kp = 2.4;
float Ki = 0.003;
float Kd = 3.65;

float calcP, calcI, calcD;
float desiredAngle = 0;

void PIDcontrole() {

  previousTime = time;
  time = millis();
  elapsedTime = (time-previousTime)/1000;

  angleX = mpu6050.getAngleX();
  angleY = mpu6050.getAngleY();
  angleZ = mpu6050.getAngleZ();

  error = angleX - desiredAngle;
  
  calcP = Kp*error;
  if (-3<error<3) {
  calcI = calcI+(Ki*error);
  } calcD = Kd*((error-previousError)/elapsedTime);
  PID = calcP+calcI+calcD;

  if(PID <- 1000) {
    PID =- 1000;
  } if(PID > 1000) {
    PID = 1000; }

  Serial.print("PID: ");
  Serial.print(PID);
  Serial.print(" | ");

  previousError = error;

}

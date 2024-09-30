#include <MPU6050_tockn.h>

const int numReadings = 10;
float readings[numReadings];  // Array para armazenar as leituras do giroscópio
int indexo = 0;
float total = 0;

float currentTime, elapsedTime, previousTime;
float PID, error, previousError;
float angleX, angleY, angleZ;
float total_angle, angle_pitch, angle_row;

float Kp = 2.4;
float Ki = 0.003;
float Kd = 3.65;

float calcP, calcI, calcD;
float desiredAngle = 0;

float gravityOffset = 90.0;  // Valor para compensar o efeito da gravidade

void filterAngleZ(float newValue) {
  total -= readings[indexo];
  readings[indexo] = newValue;
  total += newValue;
  indexo = (indexo + 1) % numReadings;
  angleZ = total / numReadings;
}

void PIDcontrole() {
  mpu6050.update();

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0;

  angleX = mpu6050.getAngleX();
  angleY = mpu6050.getAngleY();
  
  filterAngleZ(mpu6050.getAngleZ());  // Aplicando o filtro ao ângulo Z

  error = angleX - desiredAngle;

  calcP = Kp * error;
  if (-3 < error && error < 3) {
    calcI = calcI + (Ki * error);
  }
  calcD = Kd * ((error - previousError) / elapsedTime);
  PID = calcP + calcI + calcD;

  if (PID < -1000) {
    PID = -1000;
  }
  if (PID > 1000) {
    PID = 1000;
  }

  Serial.print(" | ");
  Serial.print(angleX);
  Serial.print(" | ");
  Serial.println(angleZ - gravityOffset);  // Aplicando a compensação da gravidade


  previousError = error;
}

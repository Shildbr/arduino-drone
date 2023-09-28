#include <Wire.h>

int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;

float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];

float rad_to_deg = 180/3.141592654;
float time, elapsedTime, previousTime;
float PID, error, previousError;

float Kp = 2.4;
float Ki = 0.003;
float Kd = 3.65;

float calcP, calcI, calcD;
float desiredAngle = 0;

void PIDcontrole() {

  previousTime = time;
  time = millis();
  elapsedTime = (time - previousTime) / 1000;

  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,6,true); 

  Acc_rawX=Wire.read()<<8|Wire.read();
  Acc_rawY=Wire.read()<<8|Wire.read();
  Acc_rawZ=Wire.read()<<8|Wire.read();

  Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
  Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;

  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,4,true);
  
  Gyr_rawX=Wire.read()<<8|Wire.read();
  Gyr_rawY=Wire.read()<<8|Wire.read();


  Gyro_angle[0] = Gyr_rawX/131.0;
  Gyro_angle[1] = Gyr_rawY/131.0;


  Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
  Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsedTime) + 0.02*Acceleration_angle[1];
  

  error = Total_angle[0] - desiredAngle;
  
  calcP = Kp*error;

  if (-3 <error <3) {
    calcI = calcI + (Ki*error);
  }

  calcD = Kd*((error - previousError)/elapsedTime);

  PID = calcP + calcI + calcD;

  if(PID < -1000) {
    PID=-1000;
  }

  if(PID > 1000)  {
    PID=1000;
  }

  Serial.print("PID: ");
  Serial.print(PID);
  Serial.println(" | ");

  previousError = error;

}

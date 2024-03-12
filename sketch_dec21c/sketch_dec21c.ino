
#include <MPU6050_tockn.h>
#include <PID_v1.h>
#include <Wire.h>

double Setpoint, Input, Output;

double aggKp=3, aggKi=0, aggKd=0;
double consKp=1, consKi=0, consKd=0;

PID pid(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Input = mpu6050.getAngleX();

  Setpoint = 0;

  pid.SetMode(AUTOMATIC);
}

void loop() {

  mpu6050.update();

  Input = mpu6050.getAngleX();
  
  double gap = abs(Setpoint-Input); //distance away from setpoint
  if (gap < 10)
  {  //we're close to setpoint, use conservative tuning parameters
    pid.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     pid.SetTunings(aggKp, aggKi, aggKd);
  }

  pid.Compute();
  Serial.println(Output);


}

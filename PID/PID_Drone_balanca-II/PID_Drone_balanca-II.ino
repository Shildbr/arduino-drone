
#include <MPU6050_tockn.h>
#include <Servo.h>
#include <Wire.h>

extern void PIDcontrole();
extern float PID;

float input = 1300;
float outputMotor;
float outputMotor2;

#define Esc1 D1 // Pino do servo motor 1 (controle do motor)
#define Esc2 D2 // Pino do servo motor 2 (controle do motor)

Servo esc1;
Servo esc2;

MPU6050 mpu6050(Wire);

void setup() {

  Serial.begin(250000);

  int SDA = D6;  // you can choose SDA pin
  int SCL = D5;  // you can choose SCL pin
  Wire.begin(SDA, SCL);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  esc1.attach(Esc1);  // Anexa o servo motor 1 ao pino
  esc2.attach(Esc2);  // Anexa o servo motor 2 ao pino

  esc1.writeMicroseconds(1000);  // Define o sinal mínimo do servo motor 1
  esc2.writeMicroseconds(1000);  // Define o sinal mínimo do servo motor 2

  delay(1000);

  PIDcontrole();

}

void loop() {

  mpu6050.update();
  outputMotor = input - PID;   // Calcula o sinal de saída do motor 1
  outputMotor2 = input + PID;  // Calcula o sinal de saída do motor 2

  // Limita os sinais de saída para os valores mínimos e máximos
  if (outputMotor < 1000) {
    outputMotor = 1000;
  }
  if (outputMotor > 2000) {
    outputMotor = 2000;
  }

  // Limite para o motor 2
  if (outputMotor2 < 1000) {
    outputMotor2 = 1000;
  }
  if (outputMotor2 > 2000) {
    outputMotor2 = 2000;
  }

  // Imprime informações no monitor serial


  // Controla os servo motores com os sinais calculados
  esc1.writeMicroseconds(outputMotor);
  esc2.writeMicroseconds(outputMotor2);  
  
  PIDcontrole();
}
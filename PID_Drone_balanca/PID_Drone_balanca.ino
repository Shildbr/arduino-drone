#include <SoftwareSerial.h>
#include <Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

// DECLARAÇÃO DE VARIÁVEIS
double anguloX;
double anguloY;
double anguloZ;
double erro;
double calcP;
double outputMotor;
double outputMotor2;
int potpin = A0;  // Pino do potenciômetro para ajuste de entrada
int input;

#define angulo_desejado 0  // Ângulo desejado para o controle
#define Esc1 7  // Pino do servo motor 1 (controle do motor)
#define Esc2 6  // Pino do servo motor 2 (controle do motor)

// COEFICIENTES PID
#define Kp 2.0  // Coeficiente proporcional
#define Ki 0.0  // Coeficiente integral
#define Kd 0.0  // Coeficiente derivativo

Servo esc1;
Servo esc2;

void PIDcontrole(){
  erro = anguloX - angulo_desejado;  // Cálculo do erro
}

void setup() {
  Serial.begin(74880);  // Inicialização da comunicação serial
  Wire.begin();  // Inicialização da comunicação I2C
  mpu6050.begin();  // Inicialização do sensor MPU6050
  mpu6050.calcGyroOffsets(false);  // Cálculo dos offsets do giroscópio

  esc1.attach(Esc1);  // Anexa o servo motor 1 ao pino
  esc2.attach(Esc2);  // Anexa o servo motor 2 ao pino

  esc1.writeMicroseconds(1000);  // Define o sinal mínimo do servo motor 1
  esc2.writeMicroseconds(1000);  // Define o sinal mínimo do servo motor 2
  delay(1000);

  esc1.writeMicroseconds(2000);  // Define o sinal máximo do servo motor 1
  esc2.writeMicroseconds(2000);  // Define o sinal máximo do servo motor 2
  delay(1000);
}

void loop() {
  mpu6050.update();  // Atualiza os valores do sensor MPU6050

  anguloX = mpu6050.getAngleX();  // Obtém o ângulo X do sensor
  anguloY = mpu6050.getAngleY();  // Obtém o ângulo Y do sensor
  anguloZ = mpu6050.getAngleZ();  // Obtém o ângulo Z do sensor

  erro = angulo_desejado - anguloX;  // Calcula o erro entre o ângulo desejado e o ângulo medido
  calcP = erro * Kp;  // Calcula a componente proporcional do controle

  input = analogRead(potpin);  // Lê o valor do potenciômetro
  input = map(input, 0, 1023, 1000, 2000);  // Mapeia o valor lido para o intervalo de saída do servo

  float outputMotor = input - calcP;  // Calcula o sinal de saída do motor 1
  float outputMotor2 = input + calcP;  // Calcula o sinal de saída do motor 2
  
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
  Serial.print("Input: ");
  Serial.print(input);
  Serial.print(" | ");
  Serial.print("Erro: ");
  Serial.print(erro);
  Serial.print(" | ");
  Serial.print("Angulo: ");
  Serial.print(anguloX);
  Serial.print(" | ");
  Serial.print("Output Motor 1: ");
  Serial.print(outputMotor);
  Serial.print(" | ");
  Serial.print("Output Motor 2: ");
  Serial.println(outputMotor2);

  // Controla os servo motores com os sinais calculados
  esc1.write(outputMotor);
  esc2.write(outputMotor2);
}

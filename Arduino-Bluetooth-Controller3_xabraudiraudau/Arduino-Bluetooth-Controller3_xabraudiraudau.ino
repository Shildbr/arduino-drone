#include <Servo.h>
#include <SoftwareSerial.h>
#define motor 6

SoftwareSerial mySerial(12, 13); // RX, TX

Servo esc;

String dado = "";  // Variável para armazenar os dados recebidos

String velocidadeString = "";  // Variável para armazenar a velocidade

double velocidade;
double potencia;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  mySerial.begin(115200);

  pinMode(motor, OUTPUT);
  esc.attach(motor);
  esc.writeMicroseconds(1000);  // Velocidade mínima
  delay(1000);
  esc.writeMicroseconds(2000);  // Velocidade máxima
  delay(1000);

  Serial.println("to ligadu");
  mySerial.println("Olá, mundo?");
}

void loop() { // run over and over

  if (mySerial.available())  {
    char dadoRecebido = mySerial.read();
    if (dadoRecebido == '/') {
      velocidadeString = dado;
      dado = "";
    } else {
      dado += dadoRecebido;
    }
  }

  if (velocidadeString != "") { // Verifica se a variável não está vazia e, caso não esteja, realiza o cálculo da potência
    velocidade = velocidadeString.toDouble();

    // Verifica se a velocidade está dentro da faixa esperada (0 a 100)
    if (velocidade >= 0 && velocidade <= 200) {
      // Cálculo da potência
      potencia = velocidade / 2 / 100 * 1000 + 1000;

      // Verifica se a potência está dentro dos limites aceitáveis (1000 a 2000)
      if (potencia >= 1000 && potencia <= 2000) {
        esc.writeMicroseconds(potencia); // Define a potência do servo motor
        Serial.println(potencia);
      } else {
        // Potência fora dos limites, descarta o valor recebido
        Serial.println("Potência inválida. Valor descartado.");
      }
    } else {
      // Velocidade fora da faixa, descarta o valor recebido
      Serial.println("Velocidade inválida. Valor descartado.");
    }

    velocidadeString = ""; // Limpa a variável para a próxima leitura
  }
}

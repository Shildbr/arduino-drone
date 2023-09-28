#include <SoftwareSerial.h>

#include <Servo.h>

Servo esc;

#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 13
#define REMOTEXY_SERIAL_TX 12
#define REMOTEXY_SERIAL_SPEED 9600
#define motor 6

float velocidade;
float joystick_1_y;

// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =  // 28 bytes
  { 255, 4, 0, 0, 0, 21, 0, 16, 26, 0, 5, 0, 232, 6, 48, 48, 2, 26, 31, 5,
    32, 76, 5, 48, 48, 2, 26, 31 };

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  int8_t joystick_1_x;  // from -100 to 100
  int8_t joystick_1_y;  // from -100 to 100
  int8_t joystick_2_x;  // from -100 to 100
  int8_t joystick_2_y;  // from -100 to 100

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() {
  RemoteXY_Init();
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  RemoteXY.joystick_1_y = -100;
  esc.attach(motor);
  esc.writeMicroseconds(1000);  // Velocidade mínima
  delay(1000);
  esc.writeMicroseconds(2000);  // Velocidade máxima
  delay(1000);
}

void loop() {

  RemoteXY_Handler();

  joystick_1_y = RemoteXY.joystick_1_y+100;

  velocidade = joystick_1_y/2/ 100 * 1000 + 1000;

  Serial.println(velocidade);
  esc.writeMicroseconds(velocidade);
}
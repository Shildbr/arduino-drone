/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 10
#define REMOTEXY_SERIAL_TX 11
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
}

void loop() {

  RemoteXY_Handler();

  joystick_1_y = RemoteXY.joystick_1_y+100;

  velocidade = joystick_1_y/2/ 100 * 255;

  Serial.println(velocidade);
  analogWrite(motor, velocidade);
}
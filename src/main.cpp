#include <Arduino.h>
#include "BasicLib.h"

//Tasks
Task main;
Task serial;

//Variables
bool parar;
bool desligar;
bool rodarHor;
bool rodarAnti;
bool outHor;
bool outAnti;

//FunctionBlocks
ResetSet rs1; 
ResetSet rs2;

//Logics
void sentidoHorario(){
  bool and1 = rodarHor && !desligar && !outAnti;
  bool or1 = desligar || parar;
  outHor = rs1.out(and1, or1);
}

void sentidoAntiHorario(){
  bool and1 = rodarAnti && !desligar && !outHor;
  bool or1 = desligar || parar;
  outAnti = rs2.out(and1 , or1);
}

void mainTask(){
  sentidoHorario();
  sentidoAntiHorario();
}

void serialTask(){
  TimerPulse t;
  if (Serial.available())
  {
    char c = Serial.read();
    switch (c)
    {
    case '1':
      Serial.println(parar);
      break;
    case '2':
      Serial.println(desligar);
      break;
    case '3':
      Serial.println(rodarHor);
      break;
    case '4':
      Serial.println(rodarAnti);
      break;
    case '5':
      Serial.println(outHor);
      break;
    case '6':
      Serial.println(outAnti);
      break;
    default:
      break;
    }    
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  serial.out(500, &serialTask);
  main.out(100, &mainTask);
}
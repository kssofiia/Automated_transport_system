#include <Wire.h>                       // Подключаем библиотеку для работы с аппаратной шиной I2C
#include <iarduino_I2C_Bumper.h>        // Подключаем библиотеку для работы с бампером I2C-flash
iarduino_I2C_Bumper bum(0x09);          // Объявляем объект bum для работы с функциями и методами библиотеки

#define sp_l      5 
#define dir_l     4
 
#define sp_r      6
#define dir_r     7 

#define sp_d      9
#define dir_d     8 


//Движение по линии до перекрестка
//
//while (bum.getLineAnalog(1) > 500 or bum.getLineAnalog(9) > 500){
//  linia();
//}
//go(0, 0);

float error = 0;
float Fprev = 0;
float pid = 0;
float kp = 0.002;
int err[9] = {0,0,0,0,0,0,0,0,0};
int sum_er = 0;

float left = 0;
float right = 0;
int val = 0;
int LED = 13;
unsigned long current = 0;

int from = 0, to = 0;
void setup(){                          
  //Serial.begin(9600);                // Инициируем передачу данных в монитор последовательного порта
  Serial1.begin(9600);
  bum.begin();                       // Инициируем работу с бампером
  pinMode(LED, OUTPUT);

  for (int i = 4; i < 10; i++) { 
    pinMode(i, OUTPUT);
  }
}                                           
void loop(){
  if (Serial1.available()){
    data = int(Serial1.read()) - 48;
    if (data == 1){
      go(100, 100);
      delay(2000);
      go(0, 0);
    }
    else if (data == 2){
      go(-100, -100);
      delay(2000);
      go(0, 0);
    }
    else if (data == 3){
      go(100, -100);
      delay(1500);
      go(0, 0);
    }
    else if (data == 4){
      go(-100, 100);
      delay(1500);
      go(0, 0);
    }
    else if (data == 5){
      digitalWrite(dir_d, LOW);
      analogWrite(sp_d, 255);
      delay(2000);
      analogWrite(sp_d, 0);
    }
    else if (data == 6){
      digitalWrite(dir_d, HIGH);
      analogWrite(sp_d, 255);
      delay(2000);
      analogWrite(sp_d, 0);
    }
  }
}

void linia (){
  sum_er=0;
  for (int i = 0; i < 9; i++){
    err[i] = bum.getLineAnalog(i + 1) * (i-4);
    sum_er = sum_er + err[i];
  }
  pid = sum_er * kp;// + (error - Fprev) * kd;
  //Serial.println(pid);


  go(60-pid,60+pid);
  delay(50);
}

void go (int lSpeed, int rSpeed){
  lSpeed = constrain(lSpeed,-255,255);
  if (lSpeed>=0){
    digitalWrite(dir_l, HIGH);
  }
  else{
    digitalWrite(dir_l, LOW);
  }
  analogWrite(sp_l, abs(lSpeed));
  
  rSpeed = constrain(rSpeed,-255,255);
  if (rSpeed>=0){
    digitalWrite(dir_r, LOW);
  }
  else{
    digitalWrite(dir_r, HIGH);
  }
  analogWrite(sp_r, abs(rSpeed));
}

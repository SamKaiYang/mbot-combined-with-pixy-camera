// #include <SoftwareSerial.h>
// SoftwareSerial BT(0,1);   // 接收腳(RX), 傳送腳(TX)；接HC-06之TXD、RXD；先不要用0,1,因為USB用
#include "MeOrion.h"
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
const int SRight = 11;     //右感測器輸入腳
const int SLeft = 12;      //左感測器輸入腳

int SRR;    //右感測器狀態
int SLL;    //左感測器狀態
byte byteSensorStatus=0;

uint8_t motorSpeed = 150;/* value: between -255 and 255. */

void setup()
{
  pinMode(SLeft, INPUT);
  pinMode(SRight, INPUT);
}

void loop()
{
   byteSensorStatus = 0;
  // 讀取感測器狀態值
  SRR = digitalRead(SRight);
  if(SRR == 1)
     byteSensorStatus = (byteSensorStatus | (0x01 << 1));
  SLL = digitalRead(SLeft);
  if(SLL == 1)
     byteSensorStatus = (byteSensorStatus | 0x01);
  switch(byteSensorStatus)

  {             // 　　感測器黑色:0  　白色:1
    case 0: // SL:0  SR:0
           forward() ;
            break;
    case 1: // SL:1 SR:0  //no used
            right();
            break;
    case 2: // SL:0  SR:1  //no used
             left();  
            break;
    case 3: // SL:1  SR:1 
           motorstop();
            break;
  } 
}

void motorstop()
{
  motor1.stop();
  motor2.stop();
}
 
void forward()
{
  motor1.run(-motorSpeed);
  motor2.run(motorSpeed);
}
 
void backward()
{
  motor1.run(motorSpeed);
  motor2.run(-motorSpeed);
}
 
// Let right motor keep running, but stop left motor
void right()
{
  motor1.run(motorSpeed);
  motor2.run(motorSpeed);
}
 
// Let left motor keep running, but stop right motor
void left()
{
  motor1.run(-motorSpeed);
  motor2.run(-motorSpeed);
}

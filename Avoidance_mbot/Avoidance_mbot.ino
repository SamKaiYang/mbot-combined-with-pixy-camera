#include "MeOrion.h"
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
MeUltrasonicSensor ultraSensor(PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */
uint8_t motorSpeed = 100;/* value: between -255 and 255. */

const int dangerThresh = 58;   // 10cm × 58
const byte speed = 100; // 馬達的PWM輸出值
 
long distance;      // 暫存接收訊號的高電位持續時間
 

 
byte dir = 0;     // 記錄行進狀態，0代表「前進」，1代表「右轉」。
 
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
 

void setup(){
  Serial.begin(9600);
}
 
void loop(){
   distance = ultraSensor.distanceCm();      // 讀取障礙物的距離
   if (distance>dangerThresh) 
   { // 如果距離大於10cm…
      if (dir != 0) 
      { // 如果目前的行進狀態不是「前進」
         dir = 0;          // 設定成「前進」
         motorstop(); // 暫停馬達0.5秒
         delay(500);
      }
      forward(); // 前進
   } else 
   {
      if (dir != 1) 
      { // 如果目前的狀態不是「右轉」
         dir = 1; // 設定成「右轉」
         motorstop(); // 暫停馬達0.5秒
         delay(500); 
      }
      right(); // 向右轉
   }
   delay(1000); // 持續1秒
}

#include "MeOrion.h"
uint8_t motorSpeed = 150;/* value: between -255 and 255. */

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);

void setup()
{ 
  Stop();
}

void loop()
{ 
  forward();
  delay(500);
  backward();
  delay(500);
  right();
  delay(500);
  left();
  delay(500);
  
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

void Stop()
{
  motor1.stop();
  motor2.stop();
}

#include <Arduino.h>
//#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Pixy2.h>
#include "MeOrion.h"
Pixy2 pixy;

uint8_t motorSpeed = 150;/* value: between -255 and 255. */
int signature = 0;
int x = 0;
int y = 0;
unsigned int width = 0;
unsigned int height = 0;

unsigned int area = 0;
unsigned int newarea = 0;
int Xmin = 70;
int Xmax = 200;
int maxArea = 0;
int minArea = 0;
static int i = 0;

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);

void setup()
{ 
  Stop();
  //Serial.begin(115200);
  //Serial.print("Starting...\n");
  pixy.init();
}

void loop()
{ 
  while(millis()<5000)
  {
    scan();
    area = width * height;
    maxArea = area + 1000;
    minArea = area - 1000;
  }

    scan(); 

  if(signature == 1)
  {
    newarea = width * height;
    
      if (x < Xmin)
      {     
       left();
      }
      else if (x > Xmax)
      {
       right();
      }
      else if(newarea < minArea)
      {
       forward(); 
      }
      else if(newarea > maxArea)
      {
       backward(); 
      }
      
      else
      {
        Stop(); 
      } 
   }
   else
   {
    Stop();
     }
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
  motor1.run(-motorSpeed);
  motor2.run(-motorSpeed);
}
 
// Let left motor keep running, but stop right motor
void left()
{
  motor1.run(motorSpeed);
  motor2.run(motorSpeed);
}

void Stop()
{
  motor1.stop();
  motor2.stop();
}
  
void scan()
  {
  uint16_t blocks;
  blocks = pixy.ccc.getBlocks();
  signature = pixy.ccc.blocks[i].m_signature;
  x = pixy.ccc.blocks[i].m_x;
  y = pixy.ccc.blocks[i].m_y;
  width = pixy.ccc.blocks[i].m_width;
  height = pixy.ccc.blocks[i].m_height;
  //Serial.print(blocks);
  }

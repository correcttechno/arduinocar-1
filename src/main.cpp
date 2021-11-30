#include <Arduino.h>
#include <IRremote.h>
#include <Servo.h>

/*
  ir sensor signal
  top:6375
  bottom:19125
  left:4335
  right:23205

*/

int RECV_PIN = A1;
int ServoPin = A0;

int MotorA1 = 5;
int MotorA2 = 6;

int MotorB1 = 10;
int MotorB2 = 11;

Servo Servo1;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  Servo1.attach(ServoPin);
  Servo1.write(45);

  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);

  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
}


int vatt=1024;
void Backward()
{
  analogWrite(MotorA1, vatt);
  digitalWrite(MotorA2, 0);
  analogWrite(MotorB1, vatt);
  digitalWrite(MotorB2, 0);
}

void Foward()
{
  digitalWrite(MotorA1, 0);
  analogWrite(MotorA2, vatt);
  digitalWrite(MotorB1, 0);
  analogWrite(MotorB2, vatt);
}

void Stop()
{
  digitalWrite(MotorA1, 0);
  digitalWrite(MotorA2, 0);
  digitalWrite(MotorB1, 0);
  digitalWrite(MotorB2, 0);
}


int deg = 45;
void loop()
{
  if (irrecv.decode(&results))
  {
    int value = results.value;
    Serial.println(value);
    
    switch (value)
    {
      //top bottom
    case 6375:
      Foward();
      delay(200);
      Stop();
      break;
    case 19125:
      Backward();
      delay(200);
      Stop();
      break;
      //left right
    case 4335:
      for (int degree = deg; degree <= 90; degree++)
      {
        Servo1.write(degree);
        delay(10);
      }
      deg = 90;
      break;
    case 23205:
      for (int degree = deg; degree >= 0; degree--)
      {
        Servo1.write(degree);
        delay(10);
      }
      deg = 0;
      break;
      //ok signal
    case 14535:
      Servo1.write(45);
      deg = 45;
      break;
    }

   
  }
  irrecv.resume();
}


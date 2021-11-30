#include <Arduino.h>
#include <IRremote.h>
#include <Servo.h>

/*
  ir sensor signal
  top:3877175040
  bottom:2907897600
  left:4144561920
  right:2774204160
  ok: 3810328320
*/

int RECV_PIN = A1;
int ServoPin = A0;

int MotorA1 = 5;
int MotorA2 = 6;

Servo Servo1;

decode_results results;
void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Servo1.attach(ServoPin);
  Servo1.write(45);

  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
}

int vatt = 180;
void Backward()
{
  analogWrite(MotorA1, vatt);
  analogWrite(MotorA2, 0);
}

void Foward()
{
  analogWrite(MotorA1, 0);
  analogWrite(MotorA2, vatt);
 
}

void Stop()
{
  analogWrite(MotorA1, 0);
  analogWrite(MotorA2, 0);
 
}

int deg = 45;
void loop()
{
  if (IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData);

    uint32_t value = IrReceiver.decodedIRData.decodedRawData;

    switch (value)
    {
      //top bottom
    case 3877175040:
      Foward();
      delay(500);
      Stop();
      break;
    case 2907897600:
      Backward();
      delay(500);
      Stop();
      break;
      //left right
    case 4144561920:
      for (int degree = deg; degree <= 80; degree++)
      {
        Servo1.write(degree);
        delay(10);
      }
      deg = 90;
      break;
    case 2774204160:
      for (int degree = deg; degree >= 10; degree--)
      {
        Servo1.write(degree);
        delay(10);
      }
      deg = 0;
      break;
      //ok signal
    case 3810328320:
      
      Servo1.write(45);
      deg = 45;

      break;
    case 3860463360:
      Stop();
    break;
    default:
      break;
    }
  }
  IrReceiver.resume();
  delay(100);
}

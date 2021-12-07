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

int RECV_PIN = A0;
int SukanPin = 3;
int ElPin = 11;
int GovdePin = 9;
int QolPin = 10;

int MotorA1 = 5;
int MotorA2 = 6;

Servo Sukan;
Servo El;
Servo Govde;
Servo Qol;
decode_results results;
void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Sukan.attach(SukanPin);
  El.attach(ElPin);
  Govde.attach(GovdePin);
  Qol.attach(QolPin);

  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);

  Sukan.write(45);
  pinMode(GovdePin, OUTPUT);
  pinMode(QolPin, OUTPUT);
  pinMode(ElPin, OUTPUT);
  pinMode(QolPin, OUTPUT);
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

int Qoldeg = 0;
int Govdedeg = 0;

void rotatePlus(Servo s, int deg)
{
  if (s.read() > deg)
  {
    for (int i = s.read(); i >= deg; i--)
    {
      s.write(i);
      delay(10);
    }
  }
  else
  {
    for (int i = s.read(); i <= deg; i++)
    {
      s.write(i);
      delay(10);
    }
  }
}

void loop()
{

  /*  for (int pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     El.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
   }
   for (int pos = 150; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     El.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
   } */

  if (IrReceiver.decode())
  {

    uint32_t value = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(value);
    switch (value)
    {
      // top bottom
    case 3125149440:
      rotatePlus(El, 150);
      break;
    case 3108437760:
      rotatePlus(El, 0);
      break;

    case 3141861120:
      Qol.attach(QolPin);
      rotatePlus(Qol, 170);
      break;
    case 3208707840:
      Qol.attach(QolPin);
      rotatePlus(Qol, 70);
      break;

    case 4161273600:
      Qol.detach();
      rotatePlus(Govde, 30);

      break;
    case 3927310080:
      Qol.detach();
      rotatePlus(Govde, 160);
      break;

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
      // left right
    case 4144561920:
      for (int degree = deg; degree <= 80; degree++)
      {
        Sukan.write(degree);
        delay(10);
      }
      deg = 90;
      break;
    case 2774204160:
      for (int degree = deg; degree >= 10; degree--)
      {
        Sukan.write(degree);
        delay(10);
      }
      deg = 0;
      break;
      // ok signal
    case 3810328320:

      Sukan.write(45);
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
}

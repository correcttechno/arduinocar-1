#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
/*
  ir sensor signal
  top:3877175040
  bottom:2907897600
  left:4144561920
  right:2774204160
  ok: 3810328320
*/

int RECV_PIN = A0;
int SukanPin = 8;
int ElPin = 11;
int GovdePin = 9;
int QolPin = 10;

int MotorA1 = 5;
int MotorA2 = 6;

Servo myServo;

SoftwareSerial mySerial(2, 3); // RX, TX
void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);


  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);

  
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

void rotatePlus(int s, int deg)
{

  myServo.attach(s);
 

  if (myServo.read() > deg)
  {
    for (int i = myServo.read(); i >= deg; i--)
    {
      myServo.write(i);
      delay(4);
    }
  }
  else
  {
    for (int i = myServo.read(); i <= deg; i++)
    {
      myServo.write(i);
      delay(4);
    }
  }

  delay(200);  
  myServo.detach();
}

void loop()
{

  
  String mydata = "";
  String integer = "";
  int n = 0;
  while (mySerial.available())
  {
    n++;
    char d = mySerial.read();
    mydata += d;
    delay(2);
  }

  if (mydata != "")
  {
    if (mydata.indexOf("Data:") != -1)
    {
      mydata.replace(" ","");
      int index = mydata.lastIndexOf(":");
      String deger = "";
      for (int i = index + 1; i < mydata.length(); i++)
      {
        deger += mydata[i];
      }
      int d=deger.toInt();
      

      if(mydata.indexOf("el:")!=-1){
          rotatePlus(ElPin,d);
      }
      if(mydata.indexOf("qol:")!=-1){
          rotatePlus(QolPin,d);
      }
      if(mydata.indexOf("govde:")!=-1){
          rotatePlus(GovdePin,d);
      }
      if(mydata.indexOf("sukan:")!=-1){
          rotatePlus(SukanPin,abs(90-d));
      }


      if(mydata.indexOf("ireli:")!=-1){
          Foward();
          delay(250);
           Stop();
      }
      else if(mydata.indexOf("geri:")!=-1){
          Backward();
          delay(250);
          Stop();
      }
     

      Serial.println(mydata);
      
    }
    else{
        Stop();
    }

  }
  /*  for (int pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     El.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
   }
   for (int pos = 150; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     El.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
   } */

}

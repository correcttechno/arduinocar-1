#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
}

int qdeg=0;
int gdeg=0;
int edeg=0;
bool elstatus=false;
void loop()
{   
    int qol=analogRead(A0);
    int govde=analogRead(A1);
    int el=digitalRead(A2);

    qol=map(qol,0,1023,70,170);
    govde=map(govde,0,1023,30,160);

    if(abs(qol-qdeg)>2){
        mySerial.print("qol:"+String(qol));
        qdeg=qol;
        delay(200);
    }

    if(abs(govde-qdeg)>2){
        mySerial.print("govde:"+String(govde));
        gdeg=govde;
        delay(200);
    }

    if(el!=edeg){
        edeg=el;
        if(elstatus==false){
            elstatus=true;
        }
        else{
            elstatus=false;
        }

        if(elstatus==false){
            mySerial.print("el:0");
        }
        else{
            mySerial.print("el:150");
        }
        
        delay(200);
    }
   

   /*  Serial.println("Qol:");
    Serial.println(qol);

    Serial.println("Govde:");
    Serial.println(govde);

    Serial.println("El:");
    Serial.println(el); */
    delay(100);
    
}

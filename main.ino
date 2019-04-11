#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

void setup()
{
  
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}

String door;
void loop()
{
int pir=digitalRead(7);
int ir=digitalRead(6);
Serial.println(ir);
if((pir==1)&&(ir==0))
{
digitalWrite(13,1);
digitalWrite(12,0);

door="Some one is in room and the door is open";
SendMessage();
}
else if((pir==1)&&(ir==1))
{
digitalWrite(13,1);
digitalWrite(12,0);
door="Some one is in room and the door is close";
SendMessage();
}
else if((pir==0)&&(ir==0))
{
digitalWrite(13,0);
digitalWrite(12,0);
door="No one is in room and the door is open";
SendMessage();
}
else if((pir==0)&&(ir==1))
{
digitalWrite(13,0);
digitalWrite(12,0);
door="No one is in room and the door is close";
SendMessage();
}

//if (Serial.available()>0)
//  switch(Serial.read())
//  {
//    case 's':
//      SendMessage();
//      break;
//    case 'r':
//      RecieveMessage();
//      break;
//  }
//
// if (mySerial.available()>0)
//   Serial.write(mySerial.read());
delay(30000);
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918560953690\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(door);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 

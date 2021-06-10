#include <SoftwareSerial.h>
SoftwareSerial bluetooth(0,1); // RX, TX
char BluetoothData;
int sw1 = 4;
int sw2 = 5;
int sw3 = 6;
int sw4 = 7;
int sw5 = 9;
int sw6 = 10;
int sw7 = 11;
int sw8 = 12;

void setup() 
{
 bluetooth.begin(9600);
pinMode(sw1, OUTPUT);
pinMode(sw2, OUTPUT);
pinMode(sw3, OUTPUT);
pinMode(sw4, OUTPUT);
pinMode(sw5, OUTPUT);
pinMode(sw6, OUTPUT);
pinMode(sw7, OUTPUT);
pinMode(sw8, OUTPUT);
}
void loop()
{
 while (bluetooth.available())
 {
 BluetoothData=bluetooth.read();
 if(BluetoothData=='A')
 { 
 digitalWrite(sw1,HIGH);
 bluetooth.println("switch 1 ON");
 Serial.print("switch 1 ON" ); 
 }
 if(BluetoothData=='a')
 { 
 digitalWrite(sw1,LOW);
 bluetooth.println("switch 1 OFF");
 Serial.print("switch 1 OFF" ); 
 }
 if(BluetoothData=='B')
 { 
 digitalWrite(sw2,HIGH);
 bluetooth.println("switch 2 ON");
 Serial.print("switch 2 ON" ); 
 }
 if(BluetoothData=='b')
 { 
 digitalWrite(sw2,LOW);
 bluetooth.println("switch 2 OFF");
 Serial.print("switch 2 OFF" ); 
 }
 if(BluetoothData=='C')
 { 
 digitalWrite(sw3,HIGH);
 bluetooth.println("switch 3 ON");
 Serial.print("switch 3 ON" ); 
 }
 if(BluetoothData=='c')
 { 
 digitalWrite(sw3,LOW);
 bluetooth.println("switch 3 OFF");
 Serial.print("switch 3 OFF" ); 
 }
 if(BluetoothData=='D')
 { 
 digitalWrite(sw4,HIGH);
 bluetooth.println("switch 4 ON");
 Serial.print("switch 4 ON" ); 
 }
 if(BluetoothData=='d')
 { 
 digitalWrite(sw4,LOW);
 bluetooth.println("switch 4 OFF");
 Serial.print("switch 4 OFF" ); 
 }
 if(BluetoothData=='E')
 { 
 digitalWrite(sw5,HIGH);
 bluetooth.println("switch 5 ON");
 Serial.print("switch 5 ON" ); 
 }
 if(BluetoothData=='e')
 { 
 digitalWrite(sw5,LOW);
 bluetooth.println("switch 5 OFF");
 Serial.print("switch 5 OFF" ); 
 }
 if(BluetoothData=='F')
 { 
 digitalWrite(sw6,HIGH);
 bluetooth.println("switch 6 ON");
 Serial.print("switch 6 ON" ); 
 }
 if(BluetoothData=='f')
 { 
 digitalWrite(sw6,LOW);
 bluetooth.println("switch 6 OFF");
 Serial.print("switch 6 OFF" ); 
 }
 if(BluetoothData=='G')
 { 
 digitalWrite(sw7,HIGH);
 bluetooth.println("switch 7 ON");
 Serial.print("switch 7 ON" ); 
 }
 if(BluetoothData=='g')
 { 
 digitalWrite(sw7,LOW);
 bluetooth.println("switch 7 OFF");
 Serial.print("switch 7 OFF" ); 
 }
 if(BluetoothData=='H')
 { 
 digitalWrite(sw8,HIGH);
 bluetooth.println("switch 8 ON");
 Serial.print("switch 8 ON" ); 
 }
 if(BluetoothData=='h')
 { 
 digitalWrite(sw8,LOW);
 bluetooth.println("switch 8 OFF");
 Serial.print("switch 8 OFF" ); 
 }
 if(BluetoothData=='#')
  { 
 digitalWrite(sw1,LOW);
  digitalWrite(sw2,LOW);
   digitalWrite(sw3,LOW);
    digitalWrite(sw4,LOW);
     digitalWrite(sw5,LOW);
      digitalWrite(sw6,LOW);
       digitalWrite(sw7,LOW);
        digitalWrite(sw8,LOW);
 bluetooth.println("switch all OFF");
 Serial.print("switch all OFF" ); 
 }
 if(BluetoothData=='@')
  { 
 digitalWrite(sw1,HIGH);
  digitalWrite(sw2,HIGH);
   digitalWrite(sw3,HIGH);
    digitalWrite(sw4,HIGH);
     digitalWrite(sw5,HIGH);
      digitalWrite(sw6,HIGH);
       digitalWrite(sw7,HIGH);
        digitalWrite(sw8,HIGH);
 bluetooth.println("switch all ON");
 Serial.print("switch all ON" ); 
 }
 delay(1);
 }
}







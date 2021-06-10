#include<LiquidCrystal.h>
#include <DHT.h>
#include "DHT.h"
#define ldr A0
#define status A3
#define DHTPIN 10
#define mnbt 11
#define lowbm 12
#define highbm 13
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

float rev=0;
volatile int rpm;
volatile int spd;
int oldtime=0;
int time;



double ldv=0; 
double lev=0; 
int level=0; 

int rh;
int temf;
float RH=0;
float TEMC=0;
float TEMF=0;

int btst=0;
int lbtst=0;

void isr() //interrupt service routine
{
rev++;
}
void sensor()
{
detachInterrupt(0);           //detaches the interrupt
time=millis()-oldtime;        //finds the time 
rpm=(rev/time)*60000;         //calculates rpm
spd=2*3.14*0.0015*(rpm)*60; //calculates speed in m/hr (for km/hr divide by 1000)
oldtime=millis();             //saves the current time
rev=0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("m/h:");
lcd.print(spd);
/*lcd.setCursor(0,1);
lcd.print(rpm);
lcd.print("RPM");
lcd.print("   ");*/

attachInterrupt(0,isr,RISING);
ldv=analogRead(ldr);
lev=(ldv/1023)*100;
level=lev;
lcd.setCursor(9,0);
lcd.print("%LI:");
lcd.print(level);
/* Output in lux 
float vldr=ldv/1023;
float rldr=r1*(v1-vldr)/vldr;
int llux=10000/((rldr*10)^1.334); // here r1 resistance at voltage divider here 1k, v1 is input voltage to ldr here 5v
*/

RH=dht.readHumidity(); // Relative humidity in %
TEMC= dht.readTemperature();// Read temperature as Celsius (the default)
TEMF= dht.readTemperature(true);// Read temperature as Fahrenheit (isFahrenheit = true)
rh=RH;
temf=TEMF;
lcd.setCursor(0,1);
lcd.print("FH:");
lcd.print(temf);
lcd.setCursor(6,1);
lcd.print("RH:");
lcd.print(rh);

}

void setup()
{
lcd.begin(16,2);                //initialize LCD
attachInterrupt(0,isr,RISING);  //attaching the interrupt,pin2-->ir sensor because low trigger(INT0), if high trigger (INT1) means pin3..
dht.begin();
pinMode(ldr,INPUT);
pinMode(DHTPIN,INPUT);
pinMode(highbm,OUTPUT);
pinMode(mnbt,INPUT_PULLUP);
pinMode(lowbm,INPUT_PULLUP);
pinMode(status,OUTPUT);
}
void loop()
{
btst=digitalRead(mnbt);
lbtst=digitalRead(lowbm);
delay(1000);
sensor();
if(btst==LOW)
{
digitalWrite(status,HIGH);
  if((spd>=0)&&(spd<=20))
  {
    digitalWrite(highbm,LOW);
    lcd.setCursor(13,1);
    lcd.print("LOW");
  }
  else if(spd>=500)                  //condition for low beam / high beam changing
  {
    digitalWrite(highbm,HIGH);
    lcd.setCursor(12,1);
    lcd.print("HIGH");
  }
  else
  {
    if(((TEMF>=45)&&(TEMF<=90)) && ((RH>=75)&&(RH<=100)))
    {
      if(((level>=0) && (level<=50)))
       {
             digitalWrite(highbm,HIGH);
             lcd.setCursor(12,1);
             lcd.print("HIGH");
       }
       else
        {
            digitalWrite(highbm,LOW);
            lcd.setCursor(13,1);
            lcd.print("LOW");
        }
    }
    else
    {
      if(((level>=0) && (level<=50)))
      {
            digitalWrite(highbm,HIGH);
            lcd.setCursor(12,1);
            lcd.print("HIGH");
      }
      else
      {
            digitalWrite(highbm,LOW);
            lcd.setCursor(13,1);
            lcd.print("LOW");
      }
    }
  }
}
else if(btst==HIGH)
{
  digitalWrite(status,LOW);
  if(lbtst==LOW)
  {
      digitalWrite(highbm,HIGH);
      lcd.setCursor(12,1);
      lcd.print("HIGH");
  }
  else
  {
     digitalWrite(highbm,LOW);
     lcd.setCursor(13,1);
     lcd.print("LOW");
  }
}
}
    

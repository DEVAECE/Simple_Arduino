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

/*initial data required for setting condition for lowbeam and high beam*/
float r=0.381;    // *****enter the radius of wheel*****in meters
int tempr=45;   //*****enter the beginning temperature(in fareinheat) for fog climate*****(ex;45)
int trange=30;  //*****enter the range of temperature from beginning temperature it seems to be fog climate*****(ex;30, so range 45 to (45+30=75))
int rhr=75;     //*****enter the relative humidity levels(in %) at fog *****(ex;75)
int hrange=25;  //*****enter the range of relative humidity*****(ex;25, so range 75 to (75+25=100)) 
int spdlt=50;   //*****enter the speed limit*****(ex;60)


void isr() //interrupt service routine
{
rev++;
}
void sensor()
{
detachInterrupt(0);           //detaches the interrupt
time=millis()-oldtime;        //finds the time 
rpm=(rev/time)*60000;         //calculates rpm
spd=r*rpm*0.377;              //SPEED = R * RPM * 0.377 (Km/hr)
oldtime=millis();             //saves the current time
rev=0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("kph:");
lcd.print(spd);
/*lcd.setCursor(0,1);
lcd.print(rpm);
lcd.print("RPM");
lcd.print("   ");*/

attachInterrupt(0,isr,RISING);
ldv=analogRead(ldr);          //ldr sensing light intensity and display it in lcd as percentage
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
  if((spd>=0)&&(spd<=10))              //low beam at speed brakes and in traffic areas
  {
    digitalWrite(highbm,LOW);
    lcd.setCursor(13,1);
    lcd.print("LOW");
  }
  else if(spd>=spdlt)                  //high beam in highways,let taken if speed exceed or equals to speedlimit for high beam
  {
    digitalWrite(highbm,HIGH);
    lcd.setCursor(12,1);
    lcd.print("HIGH");
  }
  else
  {
    if(((TEMF>=tempr)&&(TEMF<=(tempr+trange))) && ((RH>=rhr)&&(RH<=(rhr+hrange))))    //low beam in foggy climate
    {
      digitalWrite(highbm,LOW);
      lcd.setCursor(13,1);
      lcd.print("LOW");
    }
    else
    {
      if(((level>=0) && (level<=50)))             //high beam in less light intensity ( dark zones) 
      {
            digitalWrite(highbm,HIGH);
            lcd.setCursor(12,1);
            lcd.print("HIGH");
      }
      else
      {
            digitalWrite(highbm,LOW);             //low beam in high light intensity ( bright zones)
            lcd.setCursor(13,1);
            lcd.print("LOW");
      }
    }
  }
}
else if(btst==HIGH)                               //override automatic mode i.e., manual mode
{
  digitalWrite(status,LOW);
  if(lbtst==LOW)                                  //high beam when high beam switch is on
  {
      digitalWrite(highbm,HIGH);
      lcd.setCursor(12,1);
      lcd.print("HIGH");
  }
  else
  {
     digitalWrite(highbm,LOW);                    //low beam when low beam switch is on or high beam off
     lcd.setCursor(13,1);
     lcd.print("LOW");
  }
}
}
    

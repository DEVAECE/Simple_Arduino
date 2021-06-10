#include<LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

int sensor1 = 2;
int sensor2 = 3;
int buz = 13;
int led =12;

int Time1;
int Time2;
int Time;
int flag = 0;

int distance = 27;

float Speed;

void setup() {
  attachInterrupt(0,fun1,RISING);
  attachInterrupt(1,fun2,FALLING);

  lcd.begin(16,2);
  lcd.clear();
}

void fun1()
{
  Time1 = millis(); 
  if (flag == 0) {flag = 1;}
  else {flag = 0;}
}

void fun2()
{
  Time2 = millis();
  if (flag == 0) {flag = 1;}
  else {flag = 0;}
}


void loop() {
  if (flag == 0){
  if      (Time1 > Time2) {Time = Time1 - Time2;  Speed = (distance*1000)/Time;}
  else if (Time2 > Time1) {Time = Time2 - Time1;  Speed = (distance*1000)/Time;}
  else    {Speed = 0;}
  }
  
  if (Speed == 0) { 
    lcd.clear();
    lcd.print("SPEED MEASURMENT");
    lcd.setCursor(0, 1); 
    lcd.print("................"); 
    }
  else { 
    lcd.setCursor(2, 1); 
    lcd.print(Speed);
    lcd.print(" cm/sec");
    delay(2000);
    if (Speed >=200)//speed changing
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("OVER SPEEDING");
      delay(1000);
      lcd.clear();
      digitalWrite(buz,HIGH);
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print(Speed);
      delay(1000); 
    }
    digitalWrite(buz,LOW);
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
    Time1 = 0;
    Time2 = 0;
    }
}

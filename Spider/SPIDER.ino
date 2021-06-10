#define m11 11    // rear motor
#define m12 12

char str[2],i;
void forward()
{
   digitalWrite(m11, HIGH);
   digitalWrite(m12, LOW);
}
void backward()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, HIGH); 
}
void Stop()
{
   digitalWrite(m11, LOW);
   digitalWrite(m12, LOW);
}
void setup() 
{
  Serial.begin(9600);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
}
void loop() 
{
  while(Serial.available())
  {
    char ch=Serial.read();
    str[i++]=ch;
    
    if(str[i-1]=='1')
    {
     Serial.println("Forward");
     forward();
     i=0;
    }
    else if(str[i-1]=='2')
    {
     Serial.println("Backward");
     backward();
     i=0;
    }
    else if(str[i-1]=='3')
    {
      Serial.println("Stop");
      Stop();
      i=0;
    }
    delay(100);
  }
}

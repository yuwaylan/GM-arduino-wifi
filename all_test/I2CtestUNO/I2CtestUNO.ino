
#include <SoftwareSerial.h>//for I2C
SoftwareSerial mwifi(A2, A3);
#define readwifi A1
#define readwifi2 A0
void setup()
{
  Serial.begin(9600);
  pinMode(readwifi,INPUT);
  mwifi.begin(4800);  //設定軟體通訊速率
  Serial.println("RFID reader is ready!");
}

int last, current, t = 0;
void loop()
{ 
  int a=analogRead(readwifi);
   int b=analogRead(readwifi2);
   Serial.print("D5: ");
  Serial.print(a);
  Serial.print("  D6: ");
  Serial.println(b);
  mwifi.write("HI");  /* sends hello string */
  delay(1000);
}

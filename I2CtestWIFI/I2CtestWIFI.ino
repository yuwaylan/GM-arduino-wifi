#include <SoftwareSerial.h>
SoftwareSerial mwifi(D1,D2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mwifi.begin(4800);
Serial.println("HI UNO");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mwifi.available()){
    String val= mwifi.readString();
    Serial.println(val);
    Serial.println("HI UNO");
    
  }
delay(100);
}

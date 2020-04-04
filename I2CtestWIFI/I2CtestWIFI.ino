
#include <SoftwareSerial.h>//for I2C

SoftwareSerial mwifi(D1,D2);
void setup() {
  mwifi.begin(4800);
 Serial.begin(115200);           /* start serial for debug */

 
}

void loop() {
 /*------MEGA I2C---------------*/
   if(mwifi.available()){
    String val =mwifi.readString();
    Serial.println(val);
  }
  delay(100);
  /*------------------------------*/
}


#include <SoftwareSerial.h>//for I2C

SoftwareSerial mwifi(D2, D3);
#define sendmega D5
#define sendmega2 D6
void setup() {
  mwifi.begin(4800);
  Serial.begin(115200);           /* start serial for debug */
  pinMode(sendmega, OUTPUT);
  pinMode(sendmega2, OUTPUT);
}

void loop() {
  /*------MEGA I2C---------------*/
  if (mwifi.available()) {
    String val = mwifi.readString();
    val = val.substring(0, val.length() / 2);
    Serial.println(val);
  }
  /*------------------------------*/
  
}

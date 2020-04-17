
#include <SoftwareSerial.h>//for I2C

SoftwareSerial mwifi(D1, D2);
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
  digitalWrite(sendmega, HIGH);
  digitalWrite(sendmega2, HIGH);
  Serial.println("高高");
  delay(5000);
  digitalWrite(sendmega, HIGH);
  digitalWrite(sendmega2, LOW);
  Serial.println("高");
  delay(5000);
  digitalWrite(sendmega2, HIGH);
  digitalWrite(sendmega, LOW);
  Serial.println("中");
  delay(5000);

  Serial.println("低");
  digitalWrite(sendmega, LOW);
  digitalWrite(sendmega2, LOW);
  delay(3000);
}

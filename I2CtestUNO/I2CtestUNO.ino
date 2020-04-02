#include <SoftwareSerial.h>
SoftwareSerial muno(A4,A5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  muno.begin(4800);

}

void loop() {
  // put your main code here, to run repeatedly:
 muno.print("hi wifi!");
delay(1000);
}

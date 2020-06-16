/*move collector*/
#define readwifi A0
#define readwifi2 A1
#define LP A4
#define RP A5
void setup() {
  pinMode(LP,INPUT);
  pinMode(RP,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Rmwifi();

}


String Rmwifi() {
  int a = analogRead(readwifi);
  int b = analogRead(readwifi2);
  Serial.print("D5: ");
  Serial.print(a);
  Serial.print(F("  D6: "));
  Serial.println(b);
  if (a > 500 && b > 500) {
    
    analogWrite(LP, 255);
    analogWrite(RP, 0);
    
  }
  else if (a > 500 && b < 500) {
    analogWrite(LP, 150);
    analogWrite(RP, 0);
  }
  else if (a < 500 && b > 500) {
    analogWrite(LP, 0);
    analogWrite(RP, 255);
  }
  else if (a < 500 && b < 500) {
    analogWrite(LP, 0);
    analogWrite(RP, 0);
  }
  else {
    analogWrite(LP, 0);
    analogWrite(RP, 0);
  }
  delay(300);
}

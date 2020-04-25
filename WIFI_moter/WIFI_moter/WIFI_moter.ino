//#include <ESP8266WiFi.h>

#define Bstart 3//bird start
#define Bok 5//bird ok

#define wifiStB A0//wifi tell bird start
#define wifiOkB A1//tell wifi bird ok

#define Lstart 9//listen start
#define Lok 10//listen ok

#define wifiStL A2//wifi tell listen start
#define wifiOkL A3//tell wifi listen ok

#define LEDsendB 7//led bird send
#define LEDrecB 8//led bird rec

#define LEDsendL 12//led listen send
#define LEDrecL 13//led listen rec
/*
   3function
   1.send to server
   2.get from shoot bird and listen
   3.get from server if need to walk moter
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(wifiStB, INPUT);
  pinMode(wifiOkB, OUTPUT);
  pinMode(Bstart, INPUT);
  pinMode(Bok, OUTPUT);

  pinMode(wifiStL, INPUT);
  pinMode(wifiOkL, OUTPUT);
  pinMode(Lstart, INPUT);
  pinMode(Lok, OUTPUT);

  pinMode(LEDsendB, OUTPUT);//uno傳給互動裝置
  pinMode(LEDrecB, OUTPUT);//互動裝置傳給uno

  pinMode(LEDsendL, OUTPUT);//uno傳給互動裝置
  pinMode(LEDrecL, OUTPUT);//互動裝置傳給uno
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    //Serial.print("StB: ");
    int data = Serial.read();
  
  Serial.println(" ");
  switch(data){
    case '1':
      Bird(1);
      break;
    case '2':
     Bird(2);
     break;
    case '3':
      Listen(3);
      break;
    case '4':
      Listen(4);
      break;
    
  }
  }
  

}
String Bird(int value) {
  int StB = analogRead(wifiStB);
  

  if (StB > 255 && value == 1) { //if wifi send start bird
    analogWrite(Bstart, 255);
    digitalWrite(LEDsendB, HIGH);
  }
  else {
    analogWrite(Bstart, 0);
    digitalWrite(LEDsendB, LOW);
  }
  if (analogRead(Bok) && value == 2) { //!0=true
    analogWrite(wifiOkB, 200);
    digitalWrite(LEDrecB, HIGH);
  }
  else {
    analogWrite(wifiOkB, 0);
    digitalWrite(LEDrecB, LOW);
  }
}
String Listen(int value) {
  int StL = analogRead(wifiStL);

  if (StL > 255 && value == 3) { //if wifi send start bird
    analogWrite(Lstart, 255);
    digitalWrite(LEDsendL, HIGH);
  }
  else {
    analogWrite(Lstart, 0);
    digitalWrite(LEDsendL, LOW);
  }
  if (analogRead(Lok) && value == 4) { //!0=true
    analogWrite(wifiOkL, 200);
    digitalWrite(LEDrecL, HIGH);
  }
  else {
    analogWrite(wifiOkL, 0);
    digitalWrite(LEDrecL, LOW);
  }
}

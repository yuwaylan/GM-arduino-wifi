

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

#define motorL A4//Left moter
#define motorR A5//Right moter
#define motorSpeed 4//Speed motor
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
int dswitch;
void loop() {
  int L = 0, R = 0, S = 0;
  boolean a=false,b=false;
  if (Serial.available() > 0) {
    int data = Serial.read();
    switch (data) {
      case '1':
        dswitch = 1;
        break;
      case '2':
        dswitch = 1;
        break;
      case '3':
        dswitch = 1;
        break;
      case '4':
        dswitch = 1;
        break;
    }
  } else {
    dswitch = 0;
  }
  Bird(dswitch);
  Listen(dswitch);
  L=analogRead(motorL);
  R=analogRead(motorR);
  a=(L>100?true:false);
  b=(R>100?true:false);
  motormove(a,b,analogRead(motorSpeed));
  
}
void Bird(int value) {
  int StB = analogRead(wifiStB);
  if (StB > 255 || value == 1) { //if wifi send start bird
    analogWrite(Bstart, 255);
    digitalWrite(LEDsendB, HIGH);
    Sln("wifi send bird go");
  }
  else {
    analogWrite(Bstart, 0);
    digitalWrite(LEDsendB, LOW);
    Sln("bird dont go");
  }

  if (analogRead(Bok) && value == 2) { //!0=true //send back to wifi if shoot is ok
    analogWrite(wifiOkB, 200);
    digitalWrite(LEDrecB, HIGH);
    Sln("uno send bird been shoot");
  }
  else {
    analogWrite(wifiOkB, 0);
    digitalWrite(LEDrecB, LOW);
    Sln("bird hasn't been shoot yet");
  }
}
void Listen(int value) {
  int StL = analogRead(wifiStL);

  if (StL > 255 || value == 3) { //if wifi send start listen
    analogWrite(Lstart, 255);
    digitalWrite(LEDsendL, HIGH);
    Sln("wifi send go listen");
  }
  else {
    analogWrite(Lstart, 0);
    digitalWrite(LEDsendL, LOW);
    Sln("don't listen");
  }

  if (analogRead(Lok) || value == 4) {
    analogWrite(wifiOkL, 200);
    digitalWrite(LEDrecL, HIGH);
    Sln("had been listened");
  }
  else {
    analogWrite(wifiOkL, 0);
    digitalWrite(LEDrecL, LOW);
    Sln("haven't been listened");
  }
}
void motormove(boolean L, boolean R , boolean is_fast) {
  if (L && is_fast) {
    analogWrite(motorL, 255);
    analogWrite(motorR, 0);
    Sln(" motor frunt");
  }
  else if (L && !is_fast) {
    analogWrite(motorL, 200);
    analogWrite(motorR, 0);
    Sln( "motor slow frunt");
  }
  else if (R && is_fast) {
    analogWrite(motorR, 255);
    analogWrite(motorL, 0);
    Sln(" motor back");
  }
  else if (R && !is_fast) {
    analogWrite(motorR, 200);
    analogWrite(motorL, 0);
    Sln(" motor slow back");
  }
  else {
    analogWrite(motorR, 0);
    analogWrite(motorL, 0);
    Sln("PPPPPause");
  }
}
void Sln(String s) {
  Serial.println(s);
}

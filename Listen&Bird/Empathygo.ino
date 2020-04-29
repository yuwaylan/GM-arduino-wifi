#define pinSw 2
#define pinSwLed 3
#define pinSwOutput 5//~微動開關輸出
boolean switchState = false;

#define distance 20 //玩家與超音波的距離
#define pinTrig 11 //超音波發射腳
#define pinEcho 12 //超音波接收腳
#define pinEchoLed 8 //LED顯示
#define pinEchoOutput 9 //~聲波輸出

unsigned long duration, cm;
unsigned long before, after;

int val=analogRead(A5);

void setup() {
  Serial.begin(9600);
  //---------微動開關----------
  pinMode(pinSw, INPUT);
  pinMode(pinSwLed, OUTPUT);
  pinMode(pinSwOutput,OUTPUT);

  //---------超音波--------------
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinEchoLed, OUTPUT);
  pinMode(pinEchoOutput,OUTPUT);
  digitalWrite(pinTrig, LOW);
  digitalWrite(pinEchoLed, LOW);
  //---------90秒---------------
}

void loop() {
  // put your main code here, to run repeatedly:
  if (val > 300)
  {
    before = millis();
  }
  if (read_switch() || counter())
    digitalWrite(pinSwLed, HIGH);
    digitalWrite(pinSwOutput,HIGH);

  if (read_Trig() || counter())
    digitalWrite(pinEchoLed, HIGH);
    digitalWrite(pinEchoOutput,HIGH);
}

boolean read_Trig() {
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  duration = pulseIn(pinEcho, HIGH);

  cm = duration / 58; //聲波前進一公分需要58微秒

  if (cm < distance) //距離小於20cm時LED會亮
  {
    digitalWrite(pinEchoLed, HIGH);
    return true;
  }
  else
  {
    return false;
  }
  Serial.print(cm);
  Serial.println("cm");
  delay(100);
}

boolean read_switch() {
  switchState = digitalRead(pinSw);
  if (switchState)
    return true;
  else
    return false;
}

boolean counter() {
  after = millis();
  if (after - before > 90000)
    return true;
  else
    return false;
}





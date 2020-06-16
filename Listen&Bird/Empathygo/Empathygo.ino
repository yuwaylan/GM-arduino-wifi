#define pinSw 2
#define pinSwLed 3
#define pinSwOutput 4//~微動開關輸出
boolean switchState = false;
#define Itrig A2
#define iecho A3
#define distance 20 //玩家與超音波的距離
#define pinTrig 11 //超音波發射腳
#define pinEcho 12 //超音波接收腳
#define pinEchoLed 8 //LED顯示
#define pinEchoOutput 9 //~聲波輸出

#include <SoftwareSerial.h>//for I2C
SoftwareSerial wifi(A4, A5);
unsigned long duration, cm;
unsigned long before, after;

int val = analogRead(A5);

void setup() {
  Serial.begin(9600);
  wifi.begin(4800);
  //---------微動開關----------
  pinMode(pinSw, INPUT);
  pinMode(pinSwLed, OUTPUT);
  pinMode(pinSwOutput, OUTPUT);
  Serial.print("HI!! THIS IS ampathyGOGOGO");
  //---------超音波--------------
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinEchoLed, OUTPUT);
  pinMode(pinEchoOutput, OUTPUT);
  digitalWrite(pinTrig, LOW);
  digitalWrite(pinEchoLed, LOW);
  //---------90秒---------------
}
String sendserver = "";
void loop() {
  String t = "";
  sendserver = "";
  if (val > 300)
  {
    before = millis();
  }
  if (read_switch() || counter())
  {
    digitalWrite(pinSwLed, HIGH);
    //digitalWrite(pinSwOutput, HIGH);
    t = "&u3=1&";
  } else {
    t = "&u3=0&";
  }
  sendserver += t;
  t = "";
  if (read_Trig() )
  {
    Serial.println("近來ㄌ");
    digitalWrite(pinEchoLed, HIGH);
    // digitalWrite(pinEchoOutput, HIGH);
    t = "u2=1&";
  } else {
    t = "u2=0&";
  }
  sendserver += t;
  t = "";
  if (read_interance()) {
    t = "s=1";
  } else {
    t = "s=0";
  }
  sendserver += t;
  wifi.print(sendserver);
  Serial.println(sendserver);
  delay(800);
}

boolean read_Trig() {// 入口
  digitalWrite(Itrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Itrig, LOW);

  duration = pulseIn(iecho, HIGH);

  cm = duration / 58; //聲波前進一公分需要58微秒
  Serial.print(cm);
  Serial.println("   in cm");
  delay(100);
  if (cm < 60) //距離小於20cm時LED會亮
  {
    //digitalWrite(pinEchoLed, HIGH);
    return true;
  }
  else
  {
    return false;
  }

}

boolean read_interance() {//L
  digitalWrite(Itrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Itrig, LOW);

  duration = pulseIn(iecho, HIGH);

  cm = duration / 58; //聲波前進一公分需要58微秒

  if (cm < distance) //距離小於20cm時LED會亮
  {
    digitalWrite(pinEchoLed, HIGH);

    delay(100);
    return true;
  }
  else
  {
    delay(100);
    return false;
  }
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

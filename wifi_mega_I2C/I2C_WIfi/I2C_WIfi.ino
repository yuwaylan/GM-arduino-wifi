#include <String.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>//for I2C
#define mpin1 D5
#define mpin2 D6
#define resmega D3

const char* ssid = "GOGO";
const char* password = "qqqqqqqq";
String host = "192.168.137.1";  //網頁主機
IPAddress staticIP(192, 168, 137, 250);
IPAddress subnet(255, 255, 255, 0);
const int httpPort = 80;
WiFiServer server(httpPort);
SoftwareSerial mega(D1, D2); //建立軟體串列埠腳位 (RX, TX)

void setup()
{
  pinMode(D3, OUTPUT);//mega reset
  pinMode(D4, OUTPUT);//LED 黃
  pinMode(D5, OUTPUT);//motor1
  pinMode(D6, OUTPUT);//motor2
  pinMode(D7, OUTPUT);//LED 紅

  digitalWrite(D7, HIGH); //紅燈亮
  digitalWrite(D4, HIGH);  //黃燈亮
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");  //已連接
  Serial.print("IP: ");
  WiFi.config(staticIP, WiFi.gatewayIP(), subnet);
  delay(1000);
  Serial.println(WiFi.localIP());  //顯示IP位址
  mega.begin(4800);  //設定軟體通訊速率

  digitalWrite(D7, LOW);//紅燈
}
int counter = 0;
void loop() {
  String sendGET = "GET /ud.php?s=99&u1=99&u2=99&u3=99&c=99&r=";
  //s99 for test

  /*------MEGA I2C---------------*/
  if (mega.available()) {
    String val = mega.readString();
    Serial.println(val);
    sendGET += val;
  }
  delay(100);
  /*------------------------------*/

  connection(sendGET);//送資料到網頁
 
}

void connection(String sendGET) {
  WiFiClient client;  //客戶端物件
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed!");  //主機連線失敗
    digitalWrite(D7, HIGH);//紅燈亮
    digitalWrite(D4, LOW);//黃燈暗
    return;
  } else
  {
    digitalWrite(D7, LOW);
    digitalWrite(D4, HIGH);
    Serial.println("success");
  }
  client.print(String(sendGET) + " HTTP/1.1\r\n" + "Host: " + host + "\r\nConnection: close\r\n\r\n");  //請求網頁
  delay(800);
}

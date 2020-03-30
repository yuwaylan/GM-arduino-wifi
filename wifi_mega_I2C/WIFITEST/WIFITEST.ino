#include "ESP8266WiFi.h"
#include <SoftwareSerial.h>//for I2C
const char* ssid = "GOGO";
const char* password = "qqqqqqqq";
const char* host = "192.168.137.1";  //網頁主機
WiFiClient client;  //客戶端物件
const int httpPort = 80;  //網頁伺服器埠號
SoftwareSerial mega(D5,D6);//建立軟體串列埠腳位 (RX, TX)
void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");  //已連接
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());  //顯示IP位址
}
int counter = 0;
void loop() {
  String sendGET = "GET /ud.php?s=1&u1=0&u2=0&u3=0&c=100&r=";
  sendGET += counter;
  counter++;
  
  
  Serial.print("connect to: ");  //顯示網頁主機
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed!");  //主機連線失敗
    return;
  }
  client.print(String(sendGET) + " HTTP/1.1\r\n" + "Host: " + host + "\r\nConnection: close\r\n\r\n");  //請求網頁
  delay(10);

  while (client.available()) { //取得資料
    String line = client.readStringUntil('\r');  //一列資料
    Serial.print(line);
  }

  Serial.println();
  //Serial.println("closing connection!");
  Serial.println(counter);

  delay(1000);
  if (counter >= 5000)
    counter = 0;
}

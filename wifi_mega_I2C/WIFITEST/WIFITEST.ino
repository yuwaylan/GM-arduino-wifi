#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>//for I2C
#include <String.h>

#define Y_LED D4
#define R_LED D7
#define sendmega D5
#define sendmega2 D0
 
const char* ssid = "GOGO";
const char* password = "qqqqqqqq";
String host = "192.168.137.1";  //網頁主機
IPAddress staticIP(192, 168, 137, 250);
IPAddress subnet(255, 255, 255, 0);
const int httpPort = 80;
WiFiServer server(httpPort);
SoftwareSerial mega(D1, D2); //建立軟體串列埠腳位 (RX, TX)

int counter = 0;
String sendGET = "GET /ud.php?s=99&u1=99&u2=99&u3=99&c=99&r="; //s99 for test
void setup()
{
  pinMode(D0, OUTPUT);//mega reset
  pinMode(D4, OUTPUT);//LED 黃
  pinMode(D7, OUTPUT);//LED 紅
  pinMode(sendmega, OUTPUT);
  pinMode(sendmega2, OUTPUT);

  digitalWrite(D7, HIGH); //紅燈亮
  digitalWrite(D4, HIGH);  //黃燈亮
  Serial.begin(115200);
  mega.begin(4800);  //設定軟體通訊速率

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  Serial.println("WiFi connected!");  //已連接
  Serial.print("IP: ");
  WiFi.config(staticIP, WiFi.gatewayIP(), subnet);
  delay(1000);
  Serial.println(WiFi.localIP());  //顯示IP位址
  server.begin();

  digitalWrite(D7, LOW);//紅燈
  digitalWrite(sendmega, LOW);
  digitalWrite(sendmega2, LOW);
}
void loop() {


  WiFiClient client = server.available();
  if (!client)
  {
    Serial.print("no conec  \t");
    sendGET += Rmega();
    connection(sendGET);
    return;
  }
  while (!client.available())
  {
    digitalWrite(R_LED, HIGH);
    digitalWrite(Y_LED, HIGH);
    Serial.print(".");
    delay(1);
  }
  digitalWrite(R_LED, LOW);
  digitalWrite(Y_LED, LOW);
  sendGET = "GET /ud.php?s=99&u1=99&u2=99&u3=99&c=99&r=";
  sendGET += Rmega();
  connection(sendGET);//送資料到網頁
  String head = client.readStringUntil('\r');
  //GET /8888 HTTP/1.1
  head.replace("GET /", "");
  head.replace(" HTTP/1.1", "");
  /* Serial.print("*-");
    Serial.print(head);
    Serial.println("-*");

    Serial.print("-");
    Serial.print(head[0]);
    Serial.println("-");
    int a=head[0];
    Serial.println(a);*/


  client.println("<!DOCTYPE HTML>");
  client.println("<html><head>");
  client.println("<meta http-equiv=\"refresh\" content=\"5\" />");
  client.println("<meta http-equiv=\"Content-Type\" content=\"text/html\" charset=big-5\">");
  client.println("</head><body>");
  //client.println(sendGET);
  client.print(getinst(head));
  client.println("<hr></br><input type=\"button\" value=\"FROUNT\" onclick=\"location.href='  /f'\"> ");
  client.println("<input type=\"button\" value=\"BACK\" onclick=\"location.href='/b'\"> ");
  client.println("<input type=\"button\" value=\"PAUSE\" onclick=\"location.href='/p'\"> ");
  client.println("<input type=\"button\" value=\"LIST VALUE\" onclick=\"location.href='/s'\">");
  client.println("</body></html>");
  /*
     ##可以製作按鈕 讓他可以直接用網頁控制
     ##直接把Rmega的訊息用</>包起來，C#爬起來比較方便
  */

  client.flush();
  client.stop();
  delay(1000);




}//loop end

/*------I2C  Send Get Request-----------------*/
String Rmega() {
  Serial.print("  RM");
  if (mega.available()) {
    String val = mega.readString();
    Serial.println(val);
    return val;
  }
  else
    return "";
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
    Serial.println("  success");
  }
  client.print(String(sendGET) + " HTTP/1.1\r\n" + "Host: " + host +
               "\r\nConnection: close\r\n\r\n");  //請求網頁
  delay(800);
}


String getinst(String ins) {
  int t = ins[0];
  switch (t) {
    case 'f':
      Serial.println("Front");
      digitalWrite(sendmega, HIGH);
      digitalWrite(sendmega2, LOW);
      return "Front";
      break;
    case 'b':
      Serial.println("Back");
      digitalWrite(sendmega, LOW);
      digitalWrite(sendmega2, HIGH);
      return "Back";
      break;
    case 'p':
      Serial.println("Pause");
      digitalWrite(sendmega, LOW);
      digitalWrite(sendmega2, LOW);
      return "Pause";
      break;
    case 's':
      Serial.println("list status");
      return "list status";
      break;
    default:
      return "";
      break;
  }

}

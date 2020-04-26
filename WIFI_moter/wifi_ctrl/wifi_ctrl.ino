#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <String.h>

#define tell_bird_st D1
#define tell_listen_st D2
#define know_bird_ok D3
#define know_listen_ok D4
#define tell_motorL D5
#define tell_motorR D6
#define tell_motor_s D7
/*
   收到的訊息:
   1:小鳥開始
   2.偷聽開始
   3.馬達全速正轉
   4.馬達慢速正轉
   5.馬達反轉
   6.暫停
*/
const char* ssid = "GOGO";
const char* password = "qqqqqqqq";
String host = "192.168.137.1";  //網頁主機
IPAddress staticIP(192, 168, 137, 25);
IPAddress subnet(255, 255, 255, 0);
const int httpPort = 80;
WiFiServer server(httpPort);

int counter = 0;
String sendGET = "GET /ud.php?s=1&u1=0&u2=-1&u3=-1&c=99"; //s99 for test
void setup()
{
  pinMode(tell_bird_st, OUTPUT);
  pinMode(tell_listen_st, OUTPUT);
  pinMode(tell_motorL, OUTPUT);
  pinMode(tell_motorR, OUTPUT);
  pinMode(tell_motor_s, OUTPUT);
  pinMode(know_bird_ok, OUTPUT);
  pinMode(know_listen_ok, OUTPUT);
  Serial.begin(115200);

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

}
void loop() {


  WiFiClient client = server.available();
  if (!client)
  {
    Serial.print("no conec  \t");
    /*
       1. 監聽等待網頁連線 (等馬達 等裝置)
       2. 如果馬達狀態改變才去呼叫
       3. 如果裝置需啟動才呼叫

    */
    return;
  }
  while (!client.available())
  {
    Serial.print(".");
    delay(1);
  }
  String head = client.readStringUntil('\r');
  head.replace("GET /", "");
  head.replace(" HTTP/1.1", "");
  processmessage(head);


  client.println("<!DOCTYPE HTML>");
  client.println("<html><head>");
  client.println("<meta http-equiv=\"Content-Type\" content=\"text/html\" charset=big-5\">");
  client.println("</head><body>");
  client.println("<hr></br><input type=\"button\" value=\"FROUNT\" onclick=\"location.href='/f'\"> ");
  client.println("<hr></br><input type=\"button\" value=\"FB\" onclick=\"location.href='/g'\"> ");
  client.println("<input type=\"button\" value=\"BACK\" onclick=\"location.href='/b'\"> ");
  client.println("<input type=\"button\" value=\"PAUSE\" onclick=\"location.href='/p'\"> ");
  client.println("<input type=\"button\" value=\"LIST VALUE\" onclick=\"location.href='/s'\">");
  client.println("</body></html>");


  client.flush();
  client.stop();
  delay(1000);




}//loop end


void connection(String sendGET) {
  WiFiClient client;  //客戶端物件
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed!");  //主機連線失敗
    return;
  } else
  {
    Serial.println("  success");
  }
  client.print(String(sendGET) + " HTTP/1.1\r\n" + "Host: " + host +
               "\r\nConnection: close\r\n\r\n");  //請求網頁
  delay(800);
}


String motormove(String ins) {
  int t = ins[0];
  switch (t) {
    case 'f':
      Serial.println("Front Full speed");
      digitalWrite(tell_motorL, HIGH);
      digitalWrite(tell_motorR, LOW);
      digitalWrite(tell_motor_s, HIGH);
      return "Front";
      break;
    case 'g':
      Serial.println("Frb");
      digitalWrite(tell_motorL, HIGH);
      digitalWrite(tell_motorR, LOW);
      digitalWrite(tell_motor_s, LOW);
      return "not so Front";
      break;
    case 'b':
      Serial.println("Back");
      digitalWrite(tell_motorR, HIGH);
      digitalWrite(tell_motorL, LOW);
      return "Back";
      break;
    case 'p':
      Serial.println("Pause");
      digitalWrite(tell_motorL, LOW);
      digitalWrite(tell_motorR, LOW);
      return "Pause";
      break;

    default:
      return "";
      break;
  }
}


/*
   收到的訊息:
   1:小鳥開始
   2.偷聽開始
   3.馬達全速正轉
   4.馬達慢速正轉
   5.馬達反轉
   6.暫停
*/
String processmessage(String head) {
  switch (head[0]) {
    case 1:
      Od(tell_bird_st, HIGH);
      say("bird start");
      break;
    case 2:
      Od(tell_listen_st, HIGH);
      say("listen start");
      break;
    case 3:
    motormove("f");
      break;
    case 4:
    motormove("g");
      break;
    case 5:
    motormove("b");
      break;
    case 6:
    motormove("p");
      break;
    default:
      break;
  }
}
void Od(int pin, int ele) {
  digitalWrite(pin, ele);
}
void say(String s) {
  Serial.println(s);
}

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>//for I2C
#include <String.h>

#define tell_bird_st D1
#define tell_listen_st D2
#define know_bird_ok D3
#define know_listen_ok D4
#define tell_motorL D5
#define tell_motorR D6
#define tell_motor_s D7
 
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
  pinMode(know_bird_ok,OUTPUT);
  pinMode(know_listen_ok,OUTPUT
  
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
     * 1. 監聽等待網頁連線 (等馬達 等裝置)
     * 2. 如果馬達狀態改變才去呼叫
     * 3. 如果裝置需啟動才呼叫
     * 
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
  

  
  client.println("<!DOCTYPE HTML>");
  client.println("<html><head>");
  //client.println("<meta http-equiv=\"refresh\" content=\"5\" />");
  client.println("<meta http-equiv=\"Content-Type\" content=\"text/html\" charset=big-5\">");
  client.println("</head><body>");
  //client.println(sendGET);
  client.print(getinst(head));
  client.println("<hr></br><input type=\"button\" value=\"FROUNT\" onclick=\"location.href='/f'\"> ");
  client.println("<hr></br><input type=\"button\" value=\"FB\" onclick=\"location.href='/g'\"> ");
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
      digitalWrite(sendmega2, HIGH);
      return "Front";
      break;
      case 'g':
      Serial.println("Frb");
      digitalWrite(sendmega, HIGH);
      digitalWrite(sendmega2, LOW);
      return "not so Front";
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

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>//for I2C
#include <String.h>

#define sendmega D5
#define sendmega2 D6

const char* ssid = "GOGO";
const char* password = "qqqqqqqq";
String host = "192.168.137.1";  //網頁主機
IPAddress staticIP(192, 168, 137, 25);
IPAddress subnet(255, 255, 255, 0);
const int httpPort = 80;
WiFiServer server(httpPort);
SoftwareSerial mega(D5, D4); //建立軟體串列埠腳位 (RX, TX)

int counter = 0;
String sendGET = "GET /ud.php?r=9&c=9&u1=9"; //s99 for test
void setup()
{
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


}
void loop() {
mega.print("11111111111111111111111111111111111");
delay(550);
  WiFiClient client = server.available();
  if (!client)
  {
    Serial.print("no conec  \t");
    sendGET = "GET /ud.php?r=9&c=9&u1=9";
    sendGET += Rmega();
      Serial.println(sendGET);
    connection(sendGET);//送資料到網頁

    return;
  }
  int in = 0, endis = 0;
  in = millis();
  while (!client.available())
  { endis = millis();
    if (endis - in >= 3000)
      return;
    Serial.print(".");
    delay(1);
  }
  sendGET = "GET /ud.php?r=9&c=9&u1=9";
  sendGET += Rmega();
  connection(sendGET);//送資料到網頁
  String head = client.readStringUntil('\r');
  //GET /8888 HTTP/1.1
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
String Rmega() {//直接讓mega 傳送要的指令過來
  
  if (mega.available()) {
    Serial.print("ReadMega!");
    String val = mega.readString();
    delay(1000);
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
    return;
  } else
  {
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
       case 'x'://射小鳥
      mega.print("bird");
      Serial.println("send  bird");
      delay(800);
      break;
       case 'y'://偷聽
      mega.print("listen");
       Serial.println("send  listen");
     delay(800);
      case 'r'://偷聽
      mega.print("reset");
       Serial.println("send  reset");
     delay(800);
      break;
    default:
      return "";
      break;
  }

}

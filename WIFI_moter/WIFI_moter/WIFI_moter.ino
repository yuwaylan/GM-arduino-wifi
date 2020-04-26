#include <ESP8266WiFi.h>
/*
 * 3function
 * 1.send to server
 * 2.get from shoot bird and listen
 * 3.get from server if need to walk moter
 * 4.get from server if need to triger listen and shoot
*/



const char* ssid = "GOGO";
const char* password = "qqqqqqqq";
String host = "192.168.137.1";  //網頁主機
IPAddress staticIP(192, 168, 137, 200);
IPAddress subnet(255, 255, 255, 0);
const int httpPort = 80;
WiFiServer server(httpPort);

void setup() {
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

/* 
 *c=>key index to conform whitch is avaliable
 *s=> 狀態 是否有在玩
 *u1=> 馬達狀態
 *u2=> 偷聽狀態
 *u3=> 射擊狀態
 *r=>rfid編號
*/
String sendGET = "GET /ud.php?s=99&u1=99&u2=99&u3=99&c=99&r=";
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
    Serial.print(".");
    delay(1);
  }
  sendGET = "GET /ud.php?s=99&u1=99&u2=99&u3=99&c=99&r=";
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
  client.flush();
  client.stop();
  delay(1000);
  
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

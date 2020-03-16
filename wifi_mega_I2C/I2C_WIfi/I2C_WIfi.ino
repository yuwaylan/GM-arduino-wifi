#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>//for I2C

String WIFINAME = "GOGO";
String WIFIPASSWORD = "qqqqqqqq";
IPAddress staticIP(192, 168, 137, 250);
IPAddress subnet(255, 255, 255, 0);
SoftwareSerial mySerial(21,22);//建立軟體串列埠腳位 (RX, TX)
WiFiServer server(80);

void setup()
{
  pinMode(14, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  delay(3000);
  WiFi.disconnect();
  WiFi.begin(WIFINAME, WIFIPASSWORD);
  digitalWrite(2, HIGH);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(100);
  }
  WiFi.config(staticIP, WiFi.gatewayIP(), subnet);
  delay(3000);
  Serial.println();
  Serial.println((WiFi.localIP().toString()));
  server.begin();
  mySerial.begin(9600);  //設定軟體通訊速率
  digitalWrite(2, LOW);
}

int charis = 0;
String s="";
void loop()
{

  WiFiClient client = server.available();
  if (!client){
     digitalWrite(14, LOW);
    return;
  }
  while (!client.available()){
   digitalWrite(14, HIGH);
    delay(1);
  }  
   while (!mySerial.available()) {} 
  //直到暫存器出現訊號才跳出迴圈
  
  Serial.write(mySerial.read());  //傳輸讀取的訊號
  
  while (mySerial.available()>0) {
   //如果暫存器有訊號則不斷讀取直到沒有
    mySerial.read();
  }  

  /*-------do sth to  string s-----s=> site context -------*/
  
  /*-------------------------------------------------------*/
  sitestring(s,client);
  
}

void sitestring(String s,WiFiClient &client){
  Serial.println((client.readStringUntil('\r')));
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta http-equiv= \"refresh\" content=\" 2 \" /></head><body>");
  // to let client refresh automatically
 /*-----------------------------------------------*/
 /*-----------------------------------------------*/
   //client.println("IIIII");
  client.println(s);
  client.println("</body></html>");
  client.flush();
  client.stop();
  delay(1000);
}

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>//for I2C

String WIFINAME = "GOGO";
String WIFIPASSWORD = "qqqqqqqq";
IPAddress staticIP(192, 168, 137, 250);
IPAddress subnet(255, 255, 255, 0);
SoftwareSerial mega(D5,D6);//建立軟體串列埠腳位 (RX, TX)
WiFiServer server(80);

void setup()
{
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(115200);
  delay(3000);
  WiFi.disconnect();
  WiFi.begin(WIFINAME, WIFIPASSWORD);
  
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
     digitalWrite(D7, HIGH);
    delay(100);
  }
  WiFi.config(staticIP, WiFi.gatewayIP(), subnet);
  delay(3000);
  Serial.println();
  Serial.println((WiFi.localIP().toString()));
  server.begin();
   digitalWrite(D7, LOW);
  mega.begin(9600);  //設定軟體通訊速率
  
}

int charis = 0;
int counter_id=0;
String  s="NONE";
String recive="Recive NONE";
String url="192.168.137.1/ud.php?c=1";
//const char* urltest ="https://www.google.com.tw/";
void loop()
{
  s=mega.readString();
  //Serial.println(s);
 
 
   
  /*-------do sth to  string s-----s=> site url -------*/
  WiFiClient client;
  url=url+s;
  do{
    Serial.println(url);
    Serial.println("Not yet");
     bblink();
  }while(!client.connect(url,80));
  Serial.println("success");
  delay(300);
  client.stop();
   s="null";
}

void bblink(){
  digitalWrite(D7, HIGH);
  delay(300);
  digitalWrite(D7, LOW);
  delay(100);
 
}

 

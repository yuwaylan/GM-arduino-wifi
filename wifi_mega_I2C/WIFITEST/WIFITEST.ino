#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>//for I2C
 
 
String WIFINAME = "itsme";
String WIFIPASSWORD = "12345678";
IPAddress staticIP(192, 168, 43, 250);
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
    delay(100);
     digitalWrite(D7, HIGH);
  }
  WiFi.config(staticIP, WiFi.gatewayIP(), subnet);
  delay(3000);
  Serial.println();
  Serial.println((WiFi.localIP().toString()));
  server.begin();
  mega.begin(9600);  //設定軟體通訊速率
   digitalWrite(D7, LOW);
  
}

int charis = 0;
String  s="NONE";
void loop()
{
  WiFiClient client = server.available();
  if (!client){
     digitalWrite(D7, LOW);
    return;
  }
  while (!client.available()){
   digitalWrite(D7, HIGH);
    delay(1);
  }  
 
   while(mega.available()){
    s=mega.readString();     
    Serial.println("getla");
  }

  /*-------do sth to  string s-----s=> site context -------*/
  
  /*-------------------------------------------------------*/
  sitestring(s,client);
  
}

void sitestring(String ms,WiFiClient &client){
  Serial.println((client.readStringUntil('\r')));
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta http-equiv= \"refresh\" content=\" 1 \" /></head><body>");
  // to let client refresh automatically
 /*-----------------------------------------------*/
 /*-----------------------------------------------*/
   //client.println("IIIII");
  client.println(ms);
  client.println("</body></html>");
  Serial.print(s);
  client.flush();
  client.stop();
  //delay(1000);
}

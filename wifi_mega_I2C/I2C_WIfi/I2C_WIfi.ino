#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>//for I2C
 
 
//String WIFINAME = "itsme";
//String WIFIPASSWORD = "12345678";
 
 
String WIFINAME = "GOGO";
String WIFIPASSWORD = "qqqqqqqq";
IPAddress staticIP(192, 168, 137, 250);
IPAddress subnet(255, 255, 255, 0);
SoftwareSerial mega(D5,D6);//建立軟體串列埠腳位 (RX, TX)
WiFiServer server(80);

void setup()
{
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(115200);
  delay(3000);
  WiFi.disconnect();
  WiFi.begin(WIFINAME, WIFIPASSWORD);
  digitalWrite(D7, HIGH);digitalWrite(D4, LOW);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(100);
  }
  WiFi.config(staticIP, WiFi.gatewayIP(), subnet);
  delay(3000);
  Serial.println();
  Serial.println((WiFi.localIP().toString()));
  server.begin();
  mega.begin(4800);  //設定軟體通訊速率
  digitalWrite(D7, LOW);
  digitalWrite(D4,HIGH);
}

int charis = 0;
String s="0000";
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

  /*------MEGA I2C---------------*/
   while(mega.available() > 0){
    String val =mega.readString();
    Serial.println(val);
  }
  /*------------------------------*/
  
  /*-------do sth to  string s-----s=> site context -------*/
  
  /*-------------------------------------------------------*/
  sitestring(s,client);//SEND to client
}
//END LOOOP


  /*-------編寫網頁內容-------*/
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

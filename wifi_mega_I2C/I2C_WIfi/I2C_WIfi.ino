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
    delay(100);
  }
  WiFi.config(staticIP, WiFi.gatewayIP(), subnet);
  delay(3000);
  Serial.println();
  Serial.println((WiFi.localIP().toString()));
  server.begin();
  mega.begin(9600);  //設定軟體通訊速率
  
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
    int val =99;
    val=mega.read();
    if(val==99){
      mega.println("No read");
      Serial.println("No read");
    }
    else{
      mega.println("readed");
     }
    s="readed";
   // if(mega.read()=='\n')
      //Serial.println(val);
    s="<RFIDID>RFID :";
    s+=val;
    s+="</RFIDID>";
  }

  /*-------do sth to  string s-----s=> site context -------*/
  
  /*-------------------------------------------------------*/
  sitestring(s,client);
  
}

void sitestring(String s,WiFiClient &client){
  Serial.println((client.readStringUntil('\r')));
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta http-equiv= \"refresh\" content=\" 1 \" /></head><body>");
  // to let client refresh automatically
 /*-----------------------------------------------*/
 /*-----------------------------------------------*/
   //client.println("IIIII");
  client.println(s);
  client.println("</body></html>");
  client.flush();
  client.stop();
  //delay(1000);
}

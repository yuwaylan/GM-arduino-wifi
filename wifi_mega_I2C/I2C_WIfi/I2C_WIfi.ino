#include <ESP8266WiFi.h>

String WIFINAME="!00000000";
String WIFIPASSWORD="11111111";
IPAddress staticIP(192,168,137,250);
IPAddress subnet(255,255,255,0);

bool isconected=false;
WiFiServerSecure server(80);
void setup() {
  pinMode(14,OUTPUT);
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  delay(3000);
  WiFi.disconnect();
  WiFi.begin(WIFINAME,WIFIPASSWORD);
  digitalWrite(2,HIGH);
  while(WiFi.status() != WL_CONNECTED){//if wifi is connected=3:6
    delay(500);
  //  Serial.print(WiFi.status());
  }
  WiFi.config(staticIP,WiFi.gatewayIP(),subnet);
  delay(3000);
   digitalWrite(2,LOW);
  isconected=true;
  Serial.println("WiFi connected");
  Serial.print("local: ");
  Serial.println(WiFi.localIP());
  Serial.print("gateway: ");
  Serial.println(WiFi.gatewayIP());
  server.begin();//start server
}

void loop() {
  WiFiClient client=server.avalible();
  if(!client){return;}
  while(!client.available(){
    delay(10);
  }
  Serial.println((client.readStringUntil('\r');
  


  
  
}
void myblink(int pin){
  digitalWrite(pin,HIGH);
  delay(200);
  digitalWrite(pin,LOW);
  delay(500);
}

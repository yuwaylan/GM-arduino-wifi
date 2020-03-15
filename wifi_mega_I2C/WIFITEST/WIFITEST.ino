#include <ESP8266WiFi.h>

String WIFINAME = "GOGO";
String WIFIPASSWORD = "qqqqqqqq";
IPAddress staticIP(192, 168, 137, 250);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

void setup()
{
  pinMode(14, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
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
  digitalWrite(2, LOW);
}

int charis = 0;
void loop()
{

  WiFiClient client = server.available();
  charis += (charis >= 5 ? -4 : 1);
  if (!client)
  {
    return;
  }
  while (!client.available())
  {
    delay(1);
  }
  Serial.println((client.readStringUntil('\r')));
  // client.println("HTTP/1.1 200 OK");
  // client.println("Content-Type: text/html");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta http-equiv= \"refresh\" content=\" 2 \" /></head><body>");
  // to let client refresh automatically
  switch (charis)
  {
  case 1:
    client.println("AAAAAA");
    client.println("<br>");
    client.println(charis);
    break;
  case 2:
    client.println("BBBBBB");
    client.println("<br>");
    client.println(charis);
    break;
  case 3:
    client.println("CCCCC");
    client.println("<br>");
    client.println(charis);
    break;
  case 4:
    client.println("DDDDDD");
    client.println("<br>");
    client.println(charis);
    break;
  case 5:
    client.println("EEEEEE");
    client.println("<br>");
    client.println(charis);
    break;
  }
  // client.println(Serial.read());
  client.println("</body></html>");
  client.flush();
  client.stop();
  delay(1000);
}

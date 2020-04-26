

#define Bstart 3//bird start
#define Bok 5//bird ok

#define wifiStB A0//wifi tell bird start
#define wifiOkB A1//tell wifi bird ok

#define Lstart 9//listen start
#define Lok 10//listen ok

#define wifiStL A2//wifi tell listen start
#define wifiOkL A3//tell wifi listen ok

#define LEDsendB 7//led bird send
#define LEDrecB 8//led bird rec

#define LEDsendL 12//led listen send
#define LEDrecL 13//led listen rec

#define motorL A4//Left moter
#define motorR A5//Right moter
#define motorSpeed 4//Speed motor
/*
<<<<<<< HEAD
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
=======
   3function
   1.send to server
   2.get from shoot bird and listen
   3.get from server if need to walk moter
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(wifiStB, INPUT);
  pinMode(wifiOkB, OUTPUT);
  pinMode(Bstart, INPUT);
  pinMode(Bok, OUTPUT);

  pinMode(wifiStL, INPUT);
  pinMode(wifiOkL, OUTPUT);
  pinMode(Lstart, INPUT);
  pinMode(Lok, OUTPUT);

  pinMode(LEDsendB, OUTPUT);//uno傳給互動裝置
  pinMode(LEDrecB, OUTPUT);//互動裝置傳給uno

  pinMode(LEDsendL, OUTPUT);//uno傳給互動裝置
  pinMode(LEDrecL, OUTPUT);//互動裝置傳給uno
}
int dswitch;
void loop() {
  int L = 0, R = 0, S = 0;
  boolean a=false,b=false;
  if (Serial.available() > 0) {
    int data = Serial.read();
    switch (data) {
      case '1':
        dswitch = 1;
        break;
      case '2':
        dswitch = 1;
        break;
      case '3':
        dswitch = 1;
        break;
      case '4':
        dswitch = 1;
        break;
    }
  } else {
    dswitch = 0;
  }
  Bird(dswitch);
  Listen(dswitch);
  L=analogRead(motorL);
  R=analogRead(motorR);
  a=(L>100?true:false);
  b=(R>100?true:false);
  motormove(a,b,analogRead(motorSpeed));
  
}
void Bird(int value) {
  int StB = analogRead(wifiStB);
  if (StB > 255 || value == 1) { //if wifi send start bird
    analogWrite(Bstart, 255);
    digitalWrite(LEDsendB, HIGH);
    Sln("wifi send bird go");
  }
  else {
    analogWrite(Bstart, 0);
    digitalWrite(LEDsendB, LOW);
    Sln("bird dont go");
  }

  if (analogRead(Bok) && value == 2) { //!0=true //send back to wifi if shoot is ok
    analogWrite(wifiOkB, 200);
    digitalWrite(LEDrecB, HIGH);
    Sln("uno send bird been shoot");
  }
  else {
    analogWrite(wifiOkB, 0);
    digitalWrite(LEDrecB, LOW);
    Sln("bird hasn't been shoot yet");
  }
}
void Listen(int value) {
  int StL = analogRead(wifiStL);

  if (StL > 255 || value == 3) { //if wifi send start listen
    analogWrite(Lstart, 255);
    digitalWrite(LEDsendL, HIGH);
    Sln("wifi send go listen");
  }
  else {
    analogWrite(Lstart, 0);
    digitalWrite(LEDsendL, LOW);
    Sln("don't listen");
  }

  if (analogRead(Lok) || value == 4) {
    analogWrite(wifiOkL, 200);
    digitalWrite(LEDrecL, HIGH);
    Sln("had been listened");
  }
  else {
    analogWrite(wifiOkL, 0);
    digitalWrite(LEDrecL, LOW);
    Sln("haven't been listened");
  }
}
void motormove(boolean L, boolean R , boolean is_fast) {
  if (L && is_fast) {
    analogWrite(motorL, 255);
    analogWrite(motorR, 0);
    Sln(" motor frunt");
  }
  else if (L && !is_fast) {
    analogWrite(motorL, 200);
    analogWrite(motorR, 0);
    Sln( "motor slow frunt");
  }
  else if (R && is_fast) {
    analogWrite(motorR, 255);
    analogWrite(motorL, 0);
    Sln(" motor back");
  }
  else if (R && !is_fast) {
    analogWrite(motorR, 200);
    analogWrite(motorL, 0);
    Sln(" motor slow back");
  }
  else {
    analogWrite(motorR, 0);
    analogWrite(motorL, 0);
    Sln("PPPPPause");
  }
}
void Sln(String s) {
  Serial.println(s);
>>>>>>> 8eeadc104f4e72ea45f69afcf11c67ea2e382d50
}

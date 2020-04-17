#include <SPI.h>
#include <MFRC522.h> // 引用程式庫
#include <SoftwareSerial.h>//for I2C
/*-----------------------*/
String tags[49] = {
  "20320115313", "6242141251", "246154197251", "54235206251", "1023910251", "23048147251", "86187255250", "11715218217", "134198184251", "1021903251", "22115167250",
  "38107143251", "214160138251", "182151138251", "3812391250", "198180141251", "1341308251", "6136195251", "21415235251",
  "148133137", "19889214251", "134209195251", "246135202251", "24617746251", "246842251", "615445251", "182108195251", "221333251",
  "22966251", "3820146251", "2463205251", "11872144251", "230253145251", "19818152251", "1982166250", "2267153251", "62092250", "70207213251",
  "102162193251", "11825474250", "7024033251", "3879213251", "134133142251", "13452202251", "18245213251", "10252202251", "246242207251", "2146347251", "1665549251"
};

#define RST_PIN 49 // 讀卡機的重置腳位
#define SS_PIN 53  // 晶片選擇腳位
#define LP 7
#define RP 6
#define readwifi A1
#define readwifi2 A0

MFRC522 mfrc522(SS_PIN, RST_PIN); // 建立MFRC522物件
SoftwareSerial mwifi(A2, A3);
int last, current, t = 0;
String stag = "";

void setup()
{
  Serial.begin(9600);
  mwifi.begin(4800);  //設定軟體通訊速率
  SPI.begin();
  pinMode(LP, OUTPUT);
  pinMode(RP, OUTPUT);
  pinMode(readwifi, INPUT);
  pinMode(readwifi2, INPUT);
  mfrc522.PCD_Init(); // 初始化MFRC522讀卡機模組
  Serial.println("RFID reader is ready!");
}


void loop()
{

  /***************Read rfid tag** ******************************/
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    
    t = gettag();
    Serial.println("G");
    if (t > 0) {
      stag = "";
      stag += t;
      Serial.println(t);
      mwifi.print(stag);/* send string to wifi */
      
      Rmwifi();
    }
  }//Read rfid tag end
  //Serial.println("HI");
  Rmwifi();

  delay(800);

}//end loop

int gettag() {
  
  String tag;
  int tagid = -100;
  byte *id = mfrc522.uid.uidByte; // 取得卡片的UID
  byte idSize = mfrc522.uid.size; // 取得UID的長度
  for (byte i = 0; i < idSize; i++)
  {
    tag += id[i];
  }
  for (int i = 49; i > 0; i--) {
    if (tags[i] == tag) {
      mfrc522.PICC_HaltA(); // 讓卡片進入停止模式
      tagid = 49 - i;
      break;
    }
  }
  /*----------get tag id ---------------*/
  if (tagid != last) {
    last = tagid;
  }
  else {
    tagid = -1;
  }
  return tagid;
}//getteg end


String Rmwifi() {
  int a = analogRead(readwifi);
  int b = analogRead(readwifi2);
  Serial.print("D5: ");
  Serial.print(a);
  Serial.print("  D6: ");
  Serial.println(b);
}
void gof(){
  analogWrite(LP,255);
  analogWrite(RP,0);
  Serial.println("前進");
}
void gob(){
  analogWrite(RP,255);
  analogWrite(LP,0);
  Serial.println("後退");
}
void gop(){
  analogWrite(LP,0);
  analogWrite(RP,0);
  Serial.println("停止");
}

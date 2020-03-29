#include <SPI.h>
#include <MFRC522.h> // 引用程式庫
#include <SoftwareSerial.h>//for I2C
/*-----------------------*/
String tags[49]={
"20320115313","6242141251","246154197251","54235206251","1023910251","23048147251","86187255250","11715218217","134198184251","1021903251","22115167250",
"38107143251","214160138251","182151138251","3812391250","198180141251","1341308251","6136195251","21415235251",
"148133137","19889214251","134209195251","246135202251","24617746251","246842251","615445251","182108195251","221333251",
"22966251","3820146251","2463205251","11872144251","230253145251","19818152251","1982166250","2267153251","62092250","70207213251",
"102162193251","11825474250","7024033251","3879213251","134133142251","13452202251","18245213251","10252202251","246242207251","2146347251","1665549251"
};
/*-----------------------*/

#define RST_PIN 49 // 讀卡機的重置腳位
#define SS_PIN 53  // 晶片選擇腳位
#define Pin_D1_L  40 //lpwm
#define Pin_D2_L  42 //rpwm
#define Pin_E_L   44 //pwm enable
SoftwareSerial mwifi(12,13);// //建立軟體串列埠腳位 (RX, TX)
MFRC522 mfrc522(SS_PIN, RST_PIN); // 建立MFRC522物件
String sendmessage;int t=0;
int s=-1,u1=2,u2=2,u3=2,r=-1;
void setup()
{
  Serial.begin(115200);
  mwifi.begin(9600);  //設定軟體通訊速率
  SPI.begin();
  mfrc522.PCD_Init(); // 初始化MFRC522讀卡機模組
  pinMode(Pin_D1_L, OUTPUT);
  pinMode(Pin_D2_L, OUTPUT);
  pinMode(Pin_E_L, OUTPUT);
  Serial.println("RFID reader is ready!");
}


void loop()
{
  sendmessage="";
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
  {
    t=gettag();
    if(t>0)
    { 
      Serial.println(t);
     // mwifi.print(t);
     r=t;
    }
  }

  
 mwifi.print(sendtowifi());
   delay(300);
   /* String recive=mwifi.readString();
    Serial.print(recive);
    delay(300);
    recive="null";*/
}



int last,current;
int gettag(){
  String tag;
  int tagid=-100;
  byte *id = mfrc522.uid.uidByte; // 取得卡片的UID
  byte idSize = mfrc522.uid.size; // 取得UID的長度
  for (byte i = 0; i < idSize; i++)
    {tag+=id[i]; }
  for(int i=49;i>0;i--){
      if(tags[i]==tag){
         mfrc522.PICC_HaltA(); // 讓卡片進入停止模式
         tagid= 49-i;
         break;
      }
   }
   /*----------get tag id ---------------*/ 
 if(tagid!=last){
  //current=tagid;
  last=tagid;
 }
 else{
  tagid=-1;
 }
 return tagid;
}


String sendtowifi(){
  //sendmessage="";
  sendmessage+=s;
  sendmessage+=",";
  sendmessage+=u1;
  sendmessage+=",";
  sendmessage+=u2;
  sendmessage+=",";
  sendmessage+=u3;
  sendmessage+=",";
  sendmessage+=r;
  Serial.println(sendmessage);
  return sendmessage;
}

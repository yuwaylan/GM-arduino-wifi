#include <SPI.h>
#include <MFRC522.h> // 引用程式庫

/*-----------------------*/
String tags[49]={
"20320115313","6242141251","246154197251","54235206251","1023910251","23048147251","86187255250","11715218217","134198184251","1021903251","22115167250",
"38107143251","214160138251","182151138251","3812391250","198180141251","1341308251","6136195251","21415235251",
"148133137","19889214251","134209195251","246135202251","24617746251","246842251","615445251","182108195251","221333251",
"22966251","3820146251","2463205251","11872144251","230253145251","19818152251","1982166250","2267153251","62092250","70207213251",
"102162193251","11825474250","7024033251","3879213251","134133142251","13452202251","18245213251","10252202251","246242207251","2146347251","1665549251"
};
/*-----------------------*/

#define LEN(x) sizeof(x) / sizeof(x[0]) //陣列長度
#define RST_PIN 49 // 讀卡機的重置腳位
#define SS_PIN 53  // 晶片選擇腳位

MFRC522 mfrc522(SS_PIN, RST_PIN); // 建立MFRC522物件

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // 初始化MFRC522讀卡機模組
  Serial.println("RFID reader is ready!");
}

int last,current;
void loop()
{
  
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
  {gettag();}
   
    
}




int gettag(){
  String tag;
  int tagid;
  byte *id = mfrc522.uid.uidByte; // 取得卡片的UID
  byte idSize = mfrc522.uid.size; // 取得UID的長度
  for (byte i = 0; i < idSize; i++)
    {tag+=id[i]; }
  for(int i=49;i>0;i--){
      if(tags[i]==tag){
         //Serial.println(49-i);
         //Serial.println(tag);
         mfrc522.PICC_HaltA(); // 讓卡片進入停止模式
         tagid= 49-i;
         break;
      }
   }
   /*----------get tag id ---------------*/ 
    current=tagid;
  if(current!=last){     
    last=current;
    Serial.println( tagid);
    
    }
  
 
 return tagid;
}

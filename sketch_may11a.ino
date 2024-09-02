#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

int relayPin = 4;
int cardId[] = {"63 FB E9 2E","93 54 61 92","33 08 1B 95"}; 
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  digitalWrite(relayPin, 1);
  pinMode(relayPin,OUTPUT);
}
void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();


  for(int i = 0 ; i < sizeof(cardId) / sizeof(cardId[0]) ; i++){
    if (content.substring(1) == cardId[i]) //change here the UID of the card/cards that you want to give access
    {
      digitalWrite(relayPin, 0);
      delay(800);
      digitalWrite(relayPin, 1);
    }
  }
}
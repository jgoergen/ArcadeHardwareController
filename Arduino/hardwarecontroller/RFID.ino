// PINS /////////////////////////////////////////////////////////////////////////////////////
#define RFID_MISO_PIN           12
#define RFID_MOSI_PIN           11
#define RFID_RESET_PIN          9
#define RFID_SCK_PIN            13
#define RFID_SDA_PIN            10

MFRC522 mfrc522(RFID_SDA_PIN, RFID_RESET_PIN);

void RFID_Init() {

  SPI.begin(); 
  mfrc522.PCD_Init();
}

void RFID_Update() {

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) 
    return;
    
  Serial.print("RFID|");
  
  for (byte i = 0; i < mfrc522.uid.size; i ++)  {
    
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  
  Serial.println();
}

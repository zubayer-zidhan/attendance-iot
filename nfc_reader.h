#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D8   // Define the slave select pin (SS/CS)
#define RST_PIN D3  // Define the reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(921600);  // Start serial communication
  Serial.println("Serial Started");
  SPI.begin();         // Initiate SPI bus
  Serial.println("SPI begun");
  mfrc522.PCD_Init();  // Initiate MFRC522
  Serial.println("Scan your RFID card...");
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Card detected!");

    // Print UID of the card
    Serial.print("UID: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
  }
}
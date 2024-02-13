#include <SPI.h>
#include <MFRC522.h>
#include "uid_roll_map.h"

#include <unordered_map>
#include <string>

#define SS_PIN D8   // Define the slave select pin (SS/CS)
#define RST_PIN D3  // Define the reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void initializeNFCReader() {
  SPI.begin();         // Initiate SPI bus
  Serial.println("SPI begun");
  mfrc522.PCD_Init();  // Initiate MFRC522
  Serial.println("Scan your RFID card...");
}

void readNFCData() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("Card detected!");

    // Print UID of the card
    Serial.print("UID: ");
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(uid);

    // Convert uid String to std::string
    std::string uidStdString = uid.c_str();

    // Check if UID exists in the mapping
    auto it = uidToRollNumberMap.find(uidStdString);
    if (it != uidToRollNumberMap.end()) {
      // Print corresponding roll number
      Serial.print("Roll number: ");
      Serial.println(it->second.c_str());
    } else {
      Serial.println("Roll number not found for this UID");
    }

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
  }
}
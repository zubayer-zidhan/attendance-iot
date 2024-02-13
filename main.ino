#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include "wifi_manager.h"
#include "nfc_reader.h"
#include "http_client.h"

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize Wi-Fi
    initializeWiFi();

    // Initialize NFC reader
    initializeNFCReader();
}

void loop() {
    // Check Wi-Fi connection status and reconnect if necessary
    maintainWiFiConnection();

    // Read NFC data
    readNFCData();

    // Send data to server
    sendDataToServer();
}

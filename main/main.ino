#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include "wifi_manager.h"
#include "nfc_reader.h"
#include "websocket_connector.h"


// Declare webSocketClient and signalFlag as extern
bool signalFlag;

// Declare a previous value flag
bool previousSignalFlag = false;


void setup() {
    // Initialize serial communication
    Serial.begin(921600);

    signalFlag = false;

    // Initialize Wi-Fi
    initializeWiFi();


    // Connect to WebSocket server
    connectToWebSocket();
    delay(5000); // Delay to allow WebSocket connection to establish
    

    // Initialize NFC reader
    initializeNFCReader();


}

void loop() {
    // Check Wi-Fi connection status and reconnect if necessary
    maintainWiFiConnection();
    
    // Handle WebSocket events
    webSocketLoop();

    // Check if signalFlag has changed
    if (signalFlag != previousSignalFlag) {
        Serial.println("Signal: " + String(signalFlag));
        previousSignalFlag = signalFlag; // Update previous state

        // Output Scan your card when true
        if(signalFlag) {
          Serial.println("Reader ONLINE");
          Serial.println("Scan your RFID card...");
        } else {
          Serial.println("Reader OFFLINE");
        }
    }

    // Print NFC data only if the signalFlag has changed and is True
    if (signalFlag) {
        readNFCData();
    }
}

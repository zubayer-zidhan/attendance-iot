#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include "wifi_manager.h"
#include "nfc_reader.h"
// #include "websocket_connector.h"


// HTTPClientWrapper httpClient; // Instantiate HTTPClientWrapper


// const char* webSocketServerAddress = "192.168.1.15";
// const uint16_t webSocketServerPort = 80;


// void connectToWebSocket() {
//     Serial.println("Connecting to WebSocket server...");
//     webSocket.begin(webSocketServerAddress, webSocketServerPort, "/ws");
//     webSocket.onEvent(webSocketEvent);
// }


// void subscribeToTopic(const char* topic) {
//     String subscribeMessage = "{\"action\":\"subscribe\",\"topic\":\"" + String(topic) + "\"}";
//     webSocket.sendTXT(subscribeMessage);
// }


// void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
//     switch(type) {
//         case WStype_DISCONNECTED:
//             Serial.println("Disconnected from WebSocket server");
//             break;
//         case WStype_CONNECTED:
//             Serial.println("Connected to WebSocket server");
//             break;
//         case WStype_TEXT:
//             Serial.print("Received message: ");
//             Serial.println((char*)payload);
//             break;
//     }
// }


void setup() {
    // Initialize serial communication
    Serial.begin(921600);

    // Initialize Wi-Fi
    initializeWiFi();


    // Connect to WebSocket server
    // connectToWebSocket();
    // delay(2000); // Delay to allow WebSocket connection to establish

    // // Subscribe to a topic
    // subscribeToTopic("topic/signal");

    // Initialize NFC reader
    initializeNFCReader();


}

void loop() {
    // Check Wi-Fi connection status and reconnect if necessary
    maintainWiFiConnection();
    
    // Handle WebSocket events
    // webSocket.loop();

    // Read NFC data
    readNFCData();


}

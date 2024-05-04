#ifndef WEBSOCKET_CONNECTOR_H
#define WEBSOCKET_CONNECTOR_H

#include <WebSocketsClient.h>
#include <ESP8266WiFi.h>

#include "config.h"


WebSocketsClient webSocketClient;

extern bool signalFlag; // Flag to control NFC data reading

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.println("[WSc] Disconnected from WebSocket server");
            break;
        case WStype_CONNECTED:
            Serial.println("[WSc] Connected to WebSocket server");
            break;
        case WStype_TEXT:
            {
                // #####################
                // handle SockJs+STOMP protocol
                // #####################
                String text = (char*) payload;

                // Serial.printf("[WSc] get text: %s\n", payload);

                if (payload[0] == 'h') {
                    Serial.println("Heartbeat!");
                } else if (payload[0] == 'o') {
                    // on open connection
                    String msg = "[\"CONNECT\\naccept-version:1.1,1.0\\nheart-beat:10000,10000\\n\\n\\u0000\"]";
                    webSocketClient.sendTXT(msg);

                } else if (text.startsWith("a[\"CONNECTED")) {
                    // subscribe to "/topic/signal"
                    String msg = "[\"SUBSCRIBE\\nid:sub-0\\ndestination:/topic/signal\\n\\n\\u0000\"]";
                    webSocketClient.sendTXT(msg);
                    delay(1000);

                } else if (text.startsWith("a[\"MESSAGE\\ndestination:/topic/signal")) {
                  // Check incoming messages "ON" or "OFF"
                  // Extract the message from the text
                  int startIndex = text.indexOf("{\\\"message\\\":") + 15; // 15 is the length of "{\"message\":\""
                  int endIndex = text.indexOf("\\\"}", startIndex);
                  String message = text.substring(startIndex, endIndex);

                  Serial.println("#####Message: " + message);

                  // Set flag based on the message
                  if (message == "ON") {
                      signalFlag = true;
                  } else if (message == "OFF") {
                      signalFlag = false;
                  }
                }

                break;
            }
          case WStype_BIN:
              Serial.printf("[WSc] get binary length: %u\n", length);
              hexdump(payload, length);

              // send data to server
              // webSocket.sendBIN(payload, length);
              break;
    }
}


void connectToWebSocket() {
    Serial.println("Connecting to WebSocket server...");

    // #####################
    // create socket url according to SockJS protocol (cf. http://sockjs.github.io/sockjs-protocol/sockjs-protocol-0.3.3.html#section-36)
    // #####################
    String socketUrl = ws_baseurl;
    socketUrl += random(0, 999);
    socketUrl += "/";
    socketUrl += random(0, 999999); // should be a random string, but this works (see )
    socketUrl += "/websocket";

    // connect to websocket
    webSocketClient.begin(ws_host, ws_port, socketUrl);
    webSocketClient.setExtraHeaders(); // remove "Origin: file://" header because it breaks the connection with Spring's default websocket config
    webSocketClient.onEvent(webSocketEvent);

}

void webSocketLoop() {
    webSocketClient.loop();
}

#endif

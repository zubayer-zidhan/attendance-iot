#ifndef WEBSOCKET_CONNECTOR_H
#define WEBSOCKET_CONNECTOR_H

#include <WebSocketsClient.h>

extern WebSocketsClient webSocket;

extern const char* webSocketServerAddress;
extern const uint16_t webSocketServerPort;

void connectToWebSocket();
void subscribeToTopic(const char* topic);
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);

#endif

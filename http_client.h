#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h" // Include config.h for configuration parameters

class HTTPClientWrapper {
public:
  HTTPClientWrapper() {}

  void sendRequest(const String& endpoint) {
    HTTPClient http;
    WiFiClient client;

    Serial.print("Connecting to server: ");
    Serial.println(serverUrl);

    if (http.begin(client, serverUrl + endpoint)) {
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        String payload = http.getString();
        Serial.println("Response payload:");
        Serial.println(payload);
      } else {
        Serial.print("HTTP Error: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    } else {
      Serial.println("Connection to server failed!");
    }
  }
};

#endif

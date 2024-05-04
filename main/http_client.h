#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h"

class HTTPClientWrapper {
public:
  HTTPClientWrapper() {}

  void sendAttendanceDataToServer(const String& id) {
    HTTPClient http;
    WiFiClient client;
    
    // Construct the Authorization header
    String authHeader = "Bearer " + String(bearerToken);

    if (http.begin(client, serverUrl + publishAttendanceEndpoint)) {
      Serial.print("Connecting to server: ");
      Serial.println(serverUrl + publishAttendanceEndpoint);


      // Add the Authorization header and Content-Type header
      http.addHeader("Authorization", authHeader.c_str());
      http.addHeader("Content-Type", "application/json"); // Set content type to JSON

      // Format the request body
      String requestBody = "{\"studentID\": \"" + String(id) + "\"}";


      // Send the POST request
      int httpResponseCode = http.POST(requestBody); // Send POST request with request body
      if (httpResponseCode == 200 || httpResponseCode == 400) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        String payload = http.getString();
        Serial.print("Response payload: ");
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

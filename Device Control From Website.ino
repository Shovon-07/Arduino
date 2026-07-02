#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char ssid[] = "No Internet";
const char pass[] = "**********";
char api[] = "https://iot-backend-x17e.onrender.com/api/iot-data/";

const int ledPin = 4;    // D2 (Fan)
const int relayPin = 0;  // D3 (Light)
const int builtInLed = LED_BUILTIN;

WiFiClientSecure client;
HTTPClient http;

// Json parsing
void parseIoTData(String jsonString) {
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, jsonString);

  if (error) {
    Serial.print("JSON Parsing Failed: ");
    Serial.println(error.c_str());
    return;
  }

  JsonArray dataArray = doc["data"];

  for (JsonObject item : dataArray) {
    const char* id = item["_id"];
    const char* name = item["name"];
    bool status = item["status"];

    if (strcmp(id, "6a3e4a47306c255f6e637f73") == 0) {
      if (status == 1) {
        digitalWrite(relayPin, LOW);
      } else {
        digitalWrite(relayPin, HIGH);
      }
    } else if (strcmp(id, "6a3e4a5e306c255f6e637f74") == 0) {
      if (status == 1) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(builtInLed, OUTPUT);

  // Power connection signal
  int i = 0;
  while (i <= 2) {
    digitalWrite(builtInLed, LOW);
    delay(3000);
    digitalWrite(builtInLed, HIGH);
    delay(3000);
    i++;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Serial.print("\nConnecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nEsp is connected to the : ");
  Serial.println(ssid);

  // Ingnore HTTPS certificate verification
  client.setInsecure();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    // HTTP connection start
    if (http.begin(client, api)) {

      // Send HTTP GET request
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        String payload = http.getString();
        // Serial.println(payload);

        // Json parsing
        parseIoTData(payload);
      } else {
        Serial.print("Error code : ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }

      http.end();
    }
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(3000);
}

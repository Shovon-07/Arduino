#define BLYNK_TEMPLATE_ID "TMPL6Iiv6_nLK"
#define BLYNK_TEMPLATE_NAME "Smart home automation"
#define BLYNK_AUTH_TOKEN "gEZ1unnP2QvMfVJjbziMlQLrUv2Ygziu"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char ssid[] = "No Internet";
const char pass[] = "**********";

const int ledPin = 4;    // D2
const int relayPin = 0;  // D3

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.print("\nESP is connected: ");
  Serial.print(ssid);
  Serial.println(" & Blynk Iot");
  Serial.println(WiFi.localIP());

}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(relayPin, value);
}
BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(ledPin, value);
}

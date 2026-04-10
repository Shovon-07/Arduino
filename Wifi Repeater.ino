#include <ESP8266WiFi.h>

extern "C" {
  #include "lwip/napt.h"
}

#ifndef SOFTAP_IF
#define SOFTAP_IF 1
#endif

// Main WiFi যেটা থেকে ইন্টারনেট নিবে
const char* wifi_ssid = "MMM";
const char* wifi_pass = "mamun2850";

// Hotspot নাম
const char* ap_ssid = "Ghorar dim";
const char* ap_pass = "12345678";

#define NAPT 1000
#define NAPT_PORT 10

void setup() {
  Serial.begin(57600);
  delay(1000);

  Serial.println("\nESP8266 Repeater Starting...");

  WiFi.mode(WIFI_AP_STA);

  // মূল WiFi তে কানেক্ট
  WiFi.begin(wifi_ssid, wifi_pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to main WiFi");
  Serial.print("STA IP: ");
  Serial.println(WiFi.localIP());

  // নিজের hotspot চালু
  WiFi.softAP(ap_ssid, ap_pass);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // NAT enable
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);

  if (ret == ERR_OK) {
    ip_napt_enable_no(SOFTAP_IF, 1);
    Serial.println("NAT Enabled - Repeater Ready");
  } else {
    Serial.println("NAT Failed");
  }
}

void loop() {
}

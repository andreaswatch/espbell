#include <Arduino.h>
#include <stdlib.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "esp-baresip.h"

WiFiMulti wifiMulti;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("******", "*******");
}

bool wifi_connected = false;
bool baresip_connected = false;


static void ard_get_network_address(char *local_ip, size_t maxLen,
							 char *gw, size_t maxLenGw)
{
	strncpy(local_ip, WiFi.localIP().toString().c_str(), maxLen);
	strncpy(gw, WiFi.gatewayIP().toString().c_str(), maxLenGw);
}


void loop() {
  Serial.println("loop");
  
  int wifi_state = wifiMulti.run();
  if (WL_CONNECTED != wifi_state) {
    Serial.print("WIFI failed with state: ");
    Serial.println(wifi_state);
  } else {
    if (!wifi_connected) {
      Serial.print("WIFI connected, IP=");
      Serial1.println(WiFi.localIP().toString().c_str());
      wifi_connected = true;
    }
  }

  if (wifi_connected & !baresip_connected) {
    sipPhoneInit(ard_get_network_address);
  }
}
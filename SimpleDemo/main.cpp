// main.cpp if using PlatformIO as Arduino environment in VSCode IDE
// main.ino if using Arduino IDE

#include <Arduino.h>
#include "Sniffer.h"

// Callback function - This will be invoked from Sniffer library
void sniffer_cb(SniffSummary summary) {
  Serial.print("RSSI: ");
  Serial.print(summary.rssi);
  Serial.print("  Channel: ");
  Serial.print(summary.channel);
  Serial.print("  Peer MAC: ");
  Serial.print(summary.macAddress);
  Serial.print("  SSID: ");
  Serial.println(summary.ssid);
}

void setup() {
  // Initiallise Sniffer Library and pass to it a pointer to the callback function
  callbackPtr ptr = &sniffer_cb;
  initSniffer(ptr);
}

void loop() {
  delay(10);
}

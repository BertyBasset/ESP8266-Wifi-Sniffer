// To Do
// Post data
// modularise this
// Get this and sniff to work at the same time


#include "Arduino.h"
#include "Sniffer.h"
#include "WebRequest.h"



const char* ssid     = "BTHub5-JNSW";
const char* password = "4578acef34";
const char* host = "www.w3schools.com"; // only google.com not https://google.com
const char* page = "/html/tryit.asp?filename=tryhtml_default_default";



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
  Serial.begin(115200);
  delay(10);

  // Init and Read Web Page
  initWifi(ssid, password);
  Serial.println(webRequest(host, page));

  // Init Sniffer
  callbackPtr ptr = &sniffer_cb;
  initSniffer(ptr);

}

int a = 0;
void loop() {
  delay(10);
  a++;
  if(a> 2000) {
      disableSniffing();
      
      delay(100);
      initWifi(ssid, password);
      Serial.println(webRequest(host, page));
      enableSniffing();
      a = 0;
  }
}


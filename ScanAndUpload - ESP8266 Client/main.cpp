#include "Arduino.h"
#include "Sniffer.h"
#include "WebRequest.h"

const char* ssid     = "BTHub5-JNSW";                   // Your WiFi SSID Name
const char* password = "4578acef34";                    // Your WiFi password
const char* host     = "b3a0-86-161-121-44.ngrok.io";   // The website you are uploading to - domain part only
const char* page     = "/Sniffer";                      // The page on your website you are uploading to

void upload();    // Forward declarations

const int LIST_SIZE  = 20;
SniffSummary sniffList[LIST_SIZE];                
int listCounter = 0;

void sniffer_cb(SniffSummary summary) {                 // Sniffer Callback. This gets invoked by Sniffer.h when data has been received
  // Populate array to hold sniffer into
  if(listCounter < LIST_SIZE - 1)
    listCounter++;

  Serial.println(summary.macAddress);

  sniffList[listCounter].rssi = summary.rssi;
  sniffList[listCounter].channel = summary.channel;
  // These two are character arrays, so we can't use an equals for asginment. We have to copy one array to another
  strncpy(sniffList[listCounter].macAddress, summary.macAddress, MAC_ADDRESS_LENGTH);
  strncpy(sniffList[listCounter].ssid, summary.ssid, DATA_LENGTH);
}


void setup() {
  Serial.begin(115200);

  // Init Sniffer
  callbackPtr ptr = &sniffer_cb;
  initSniffer(ptr);
}

void loop() {
  delay(10);
  // We are doing this here instead of in sniffer_cb because the callback might bet called when we are uploading otherwise
  if(listCounter >= LIST_SIZE - 1) {
      upload();
    listCounter = 0;
  }
}

void upload() {
  disableSniffing();

  // Build Payload for posting to WebApi
  // Let's be lazy and use string rather than static character arrays and the like
  String payload = "";

  for(int i = 1; i <LIST_SIZE; i++) {
    payload += String(sniffList[i].rssi) + "\t";
    payload += String(sniffList[i].channel) + "\t";
    payload += sniffList[i].macAddress;
    payload += "\t";
    payload += sniffList[i].ssid;
    payload += "\r\n";
  }

  initWifi(ssid, password);
  Serial.println(webRequest(host, page, "POST", payload));

  enableSniffing();
}

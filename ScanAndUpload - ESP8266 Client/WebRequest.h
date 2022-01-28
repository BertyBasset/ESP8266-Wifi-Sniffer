#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void initWifi(String ssid, String password) {

  Serial.print("Connecting to ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

String webRequest(String host, String page, char* requestType, String postContent = "") {
  if(requestType != "GET" && requestType != "POST") {
      Serial.println("Request Type must be GET or POST");
      return "";
  }


  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure client;
  const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS!
  
  client.setInsecure(); // this is the magical line that makes everything work
  
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    return "";
  }


  HTTPClient http;
  String url = "https://" + host + page;
  Serial.print("Requesting:  ");
  Serial.println(url);

  http.begin(client, url);
  
  int httpCode = -1;
  if(requestType == "GET")
     httpCode = http.GET();
  else {	
    http.addHeader("Content-Type", "text/plain");
    httpCode = http.POST(postContent);
  }
  Serial.print("Response Code: ");
  Serial.println(httpCode);
  
  if(httpCode > 0)
    return http.getString();

 return "connection error";
}

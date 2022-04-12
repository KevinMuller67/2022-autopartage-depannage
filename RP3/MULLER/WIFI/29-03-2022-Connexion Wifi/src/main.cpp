#include <Arduino.h>
// Load Wi-Fi library
#include <WiFi.h>

const char* ssid = "Livebox-5520";
const char* password = "53FCFF3DA2A25C6FAFC73FF355";

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop(){
 
}


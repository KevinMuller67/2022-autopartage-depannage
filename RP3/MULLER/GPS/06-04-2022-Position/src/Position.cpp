#include "Position.h"
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <TinyGPS++.h>

Position::Position(int pin)
{ const char* ssid = "Livebox-5520";
const char* password = "53FCFF3DA2A25C6FAFC73FF355";
static const uint32_t GPSBaud = 9600;
}

void Position::WIFI() {
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
  {
  Serial.begin(115200);
  ss.begin(GPSBaud);
}

void Position::Position_GPS() {
{
    while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
      delay(2000);
    };
}
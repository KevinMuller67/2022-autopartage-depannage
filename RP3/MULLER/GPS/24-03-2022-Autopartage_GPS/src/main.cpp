#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <Arduino.h>

static const int RXPin = 4, TXPin = 2;          //On initialise les broches de transmission et réception
static const uint32_t GPSBaud = 9600;           //On indique la vitesse du capteur GPS 9600 bauds
TinyGPSPlus gps;                                //On inclu une librairie                        
SoftwareSerial ss(RXPin, TXPin);
const char* ssid = "Livebox-5520";
const char* password = "53FCFF3DA2A25C6FAFC73FF355";


void setup()
{
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



void displayInfo()                                //loop pour obtenir la location du GPS
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);              //SI la position du GPS est valide alors il affiche la lattitude et longitude
  }
  else
  {
    Serial.print(F("INVALID"));                        // Sinon il affiche invalid
  }

  Serial.print(F("  Date/Time: "));                    // Si la position du GPS est valide alors il affiche la date et l'heure
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));                          // Sinon il affiche invalid
  }
  Serial.print(F(" "));
  if (gps.time.isValid())                                // Si la position du GPS est valide alosr il affiche heure/minute/seconde et centisecond
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}

void loop()
{
  delay(2000);
  displayInfo();
  /*
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }*/
}
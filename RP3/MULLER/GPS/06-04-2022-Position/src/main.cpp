#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <TinyGPS++.h>
#include <Position.h>
#include <Arduino.h>

static const int RXPin = 4, TXPin = 2;


void setup() {

  SerialBT.begin("ESP32_Kevin"); //Nom de l'ESP
}

void loop() 
{
  position.Position_GPS();
      Serial.println("Position GPS:");
       delay(2000);}

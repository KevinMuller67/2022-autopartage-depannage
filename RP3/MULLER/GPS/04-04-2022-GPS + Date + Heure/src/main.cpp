#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(115200);
  ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      // Latitude in degrees (double)
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);      
      // Longitude in degrees (double)
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6); 

      // Day (1-31) (u8)
      Serial.print("Jour = "); 
      Serial.println(gps.date.day()); 
      // Month (1-12) (u8)
      Serial.print("Mois = "); 
      Serial.println(gps.date.month()); 
      // Year (2000+) (u16)
      Serial.print("Année = "); 
      Serial.println(gps.date.year()); 
      // Hour (0-23) (u8)
      Serial.print("Heure = "); 
      Serial.println(gps.time.hour()); 
      // Minute (0-59) (u8)
      Serial.print("Minute = "); 
      Serial.println(gps.time.minute()); 
      delay(10000);
    }
  }
}
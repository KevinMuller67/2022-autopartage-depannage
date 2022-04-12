#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>               
#include <BlynkSimpleEsp32.h>

float latitude , longitude;
String  latitude_string , longitiude_string;

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64  


const char *ssid =  "Your_SSID";     
const char *pass =  "Your_Password"; 
char auth[] = "ec8EX0fnX1y78Oo6pO8lp8Of_AWUd***"; 

WidgetMap myMap(V0); 
WiFiClient client;
TinyGPSPlus gps;
HardwareSerial SerialGPS(2);


void setup()
{
  Serial.begin(115200);

  }
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");             
  }
  Serial.println("");
  Serial.println("WiFi connected!");

  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V0, "clr"); 
}
void loop()
{
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        latitude_string = String(latitude , 6);
        longitude = gps.location.lng();
        longitiude_string = String(longitude , 6);
        Serial.print("Latitude = ");
        Serial.println(latitude_string);
        Serial.print("Longitude = ");
        Serial.println(longitiude_string);
        

 
        Blynk.virtualWrite(V0, 1, latitude, longitude, "Location");
        display.display();
      }
     delay(1000);
     Serial.println();  
    }
  }  
  Blynk.run();
}
 

#include <TinyGPS++.h>                       //inclusla bibliothéque pour faire fonctionner le module GPS
#include <SoftwareSerial.h>                  //inclus la bibliothéque pour la communication série
static const int RXPin = 4, TXPin = 2;       //initialise les broches déstinées à RX et RX
static const uint32_t GPSBaud = 9600;        //initialise la vitesse de transmission série du module GPS
TinyGPSPlus gps;                             //construction de l'objet
SoftwareSerial ss(RXPin, TXPin);             //connexion série au module GPS
void setup(){
  Serial.begin(115200);                      //vitesse de la transmission série de l'ESP32
  ss.begin(GPSBaud);
}
void loop(){
  while (ss.available() > 0){                //affiche les informations à chaque fois qu'une nouvelle trame est correctement encodée
    gps.encode(ss.read());                   //décodage de la trame
    if (gps.location.isUpdated()){           
      Serial.print("Latitude= ");            //affichage la lattitude
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");          //affiche la longitude
      Serial.println(gps.location.lng(), 6);
    }
  }
}
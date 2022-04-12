#include <WiFi.h>
#include <esp_wifi.h>


void setup(){
  String hostname = "ESP32-voiture1";
  WiFi.setHostname(hostname.c_str()); //define hostname
  Serial.begin(115200);
  Serial.println();
  
  WiFi.mode(WIFI_STA);
  
  Serial.print(" ESP32 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  WiFi.begin("Livebox-5520", "53FCFF3DA2A25C6FAFC73FF355");

  Serial.print("Connection en cours");
  while (WiFi.status() != WL_CONNECTED) // tant que l'esp n'est pas connecté au réseau on attends
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connecté, adresse IP : ");
  Serial.println(WiFi.localIP()); // affichage de l'adresse IP
}
 
void loop(){

}
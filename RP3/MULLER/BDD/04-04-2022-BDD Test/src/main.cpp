// importe toutes les bibliothèques requises
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#autre
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#fin si

#include <Fil.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
const char* ssid = "xxxxxxxxxx" ;
const char* mot de passe = "xxxxxxxx" ;
Adafruit_BME280 bme ; // I2C
//Adafruit_BME280 bme(BME_CS); // SPI matériel
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // logiciel SPI
Chaîne SensorName = "BME280" ;
Emplacement du capteur de chaîne = "ESP32" ;
#define RETRY_LIMIT 20
int rtl = RETRY_LIMIT ;
void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid,mot de passe);
    tandis que (WiFi.status()!= WL_CONNECTED){
      retard (500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connecté");
    Serial.println("Adresse IP");
    Serial.println(WiFi.localIP());
  // (vous pouvez également passer un objet de bibliothèque Wire comme &Wire2)
  état booléen = bme.begin(0x76);
  si (!statut) {
    Serial.println("Impossible de trouver un capteur BME280 valide, vérifiez le câblage ou modifiez l'adresse I2C !");
    tandis que (1);
    }
}
boucle vide ()
{
    float h =bme.readHumidity();
    float t = bme.readTemperature();
    float p =(bme.readPressure()/100.0F);
    retard (500);
    tandis que (estnan(t) || estnan(h)){
      Serial.println("Vérifiez à nouveau le capteur - " + rtl);
       h = bme.readHumidity();
       t= bme.readTemperature();
      retard (500);
      si (--rtl < 1){
        ESP.restart(); // Parfois, le BME280 ne cessait de renvoyer NAN. Un redémarrage a corrigé cela.
      }
    }  
    //Ouvre une connexion au serveur
      HTTPClient http ;
      http.begin("http://192.168.29.183/ESP32/writedata.php");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    //formatez votre requête POST.
    //SensorName,location,Tempraure,Humidity,Pressure
      int httpResponseCode = http.POST("&NomCapteur=" + NomCapteur
                          + "&location=" + sensorLocation + "&Temperature=" + String(t)
                          + "&Humidité=" + Chaîne(h)+ "&Pression=" + Chaîne(p) + "");

      si (httpResponseCode >0){
          //vérifier un code de retour - C'est plus pour le débogage.
        Réponse de chaîne = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(réponse);
      }
      autre{
        Serial.print("Erreur lors de l'envoi du message");
        Serial.println(httpResponseCode);
      }
    //ferme la requête HTTP.
      http.end();
    // Surveiller les valeurs dans la console pour le débogage.
      Serial.println("Temp = " + String(t));
      Serial.println("humidité = " + String(h));  
      Serial.println("Pression = " + String(p));
   // attendre 1 minutes pour la prochaine lecture
    retard (10000);
}
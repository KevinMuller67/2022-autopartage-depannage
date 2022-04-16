//Ce programme permet d'activer et désactiver l'actionneur en envoyant un caractère par Bluetooth
//'0' en bluetooth pour faire sortir l'actionneur (mode: vérouillé véhicule)
//'1' en bluetooth pour faire rentrer l'actionneur (mode: déverouillé véhicule)
//L'ESP utilisé est l'ESP D1 R32 et la broche utilisée est le GPIO25 

//On inclue les bibliothèques
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Porte.h>

#define RELAY_PIN 25 // GPIO25 de l'ESP32 connecté à la broche IN de la carte relais

BluetoothSerial SerialBT; //On défini la connexion Bluetooth

Porte porte(RELAY_PIN);


void setup() 
{
  SerialBT.begin("ESP32_B2_Karim"); //Nom de l'ESP
}

void loop() 
{
  int valBT = 0;

  if (SerialBT.available()) 
  { //tester si une donnée est arrivée par Bluetooth
    valBT = SerialBT.read();
    if (valBT == '1') //Ouverture de la porte
    {
      porte.Ouvre();
      Serial.println("okay okay, le véhicule est déverouillé");
      delay(500);
    }
    if (valBT == '0') //Fermeture de la porte
    {
      porte.Ferme();
      Serial.println("okay okay, le véhicule est vérouillé");
      delay(500);
    }
  }
}
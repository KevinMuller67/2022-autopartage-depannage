#include <Arduino.h>
#include <LibPorte.h>


//#define RELAY_PIN 25 // GPIO25 de l'ESP32 connecté à la broche IN de la carte relais


LibPorte::LibPorte(int pin)
{
    pinMode(pin, OUTPUT);
    _pin = pin ;
}



void LibPorte::FonctionPorte()
{
   int valBT = 0;
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
  // Serial.write(SerialBT.read()); 

  //Si on envoie '1' l'actionneur est alimenté 
       if (valBT == '1'){
      digitalWrite(_pin, HIGH);
      Serial.println("***************************** okay okay, le véhicule est déverouillé *****************************");
       delay(500);
      } 
  //Si on envoie '0' l'actionneur n'est plus alimenté
      else if (valBT == '0'){
      digitalWrite(_pin, LOW);
      Serial.println("***************************** okay okay, le véhicule est vérouillé *****************************");
      delay(500);
       }
}

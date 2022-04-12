#include "Porte.h"
#include <BluetoothSerial.h>

//On autorise le bluetooth et on défini la broche du signal
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

  /*Porte(int pin);
    void Ferme();
    void Ouvre();*/

Porte::Porte(int pin)
{
  Serial.begin(115200);
  Serial.println("L'ESP a démarré, vous pouvez le connecter en Bluetooth !");
  pinMode(pin, OUTPUT); //On défini l'actionneur en sortie
  pinPorte = pin;
}

void Porte::Ouvre()
{
    digitalWrite(pinPorte, HIGH);
}

void Porte::Ferme()
{
    digitalWrite(pinPorte, LOW);
}



/*
void Porte::Bip()
{
    int valBT = 0;
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
  // Serial.write(SerialBT.read()); 

  //Si on envoie '1' l'actionneur est alimenté 
       if (valBT == '1'){
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("okay okay, le véhicule est déverouillé");
       delay(500);
      } 
  //Si on envoie '0' l'actionneur n'est plus alimenté
      else if (valBT == '0'){
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("okay okay, le véhicule est vérouillé");
      delay(500);
       }

}*/

/*
Porte::Porte(int valBT)
{
  pinMode(RELAY_PIN, OUTPUT);
  valBT = 0;
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
}



void Porte::FonctionPorte()
{
   int valBT = 0;
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
}

void Porte::Ouv()
{
       int valBT = 0;
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
     if (valBT == '1'){
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("***************************** okay okay, le véhicule est déverouillé *****************************");
       delay(500);
      } 
}

void Porte::Ferm()
{
       int valBT = 0;
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
      if (valBT == '0'){
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("***************************** okay okay, le véhicule est vérouillé *****************************");
      delay(500);
       }
}
*/

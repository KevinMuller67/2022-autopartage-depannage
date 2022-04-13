//CetTE Application permet d'activer et désactiver l'actionneur en envoyant un caractère par Bluetooth
//'0' en bluetooth pour faire sortir l'actionneur (mode: vérouillé véhicule)
//'1' en bluetooth pour faire rentrer l'actionneur (mode: déverouillé véhicule)
//L'ESP utilisé est l'ESP D1 R32 et la broche utilisé est le GPIO25 
//On inclue les librairies
#include <Arduino.h>
#include <BluetoothSerial.h>

//On autorise le bluetooth et on défini la broche du signal
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define RELAY_PIN 25 // GPIO25 de l'ESP32 connecté à la broche IN de la carte relais

//On défini la connexion bluetooth 
BluetoothSerial SerialBT;

void setup() {
  //On règle la connexion série à 115200 bauds -à supp pour le prgm def-
  Serial.begin(115200);
  SerialBT.begin("ESP32_B2_Karim"); //Nom de l'ESP
  Serial.println("L'ESP a démarré, vous pouvez le connecter en Bluetooth !");
  //On défini l'actionneur en sortie
  pinMode(RELAY_PIN, OUTPUT);
}

//à faire : le client devra envoyer un code reçu au préalable par sms (ex: 505) qu'il devra rentrer, si le code est bon, on permettra au prgm d'executer la fonction, si non on n'autorisera pas 
//Programme mini, il va falloir rajouter la fonction qui permet d'O/F par authentification du véhicule, une clé serra attribuée au client pour O/F UN SEUL véhicule choisi
void FonctionPorte() //définition de la fonction
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
}

void loop() 
{
  //on teste si on veut O/F la porte
  FonctionPorte(); //appel de la fonction
}
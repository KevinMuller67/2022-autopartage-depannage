//CetTE Application permet d'activer et désactiver l'actionneur en envoyant un caractère par Bluetooth
//'a' en bluetooth pour faire sortir l'actionneur (mode: vérouillé véhicule)
//'b' en bluetooth pour faire rentrer l'actionneur (mode: déverouillé véhicule)
//L'ESP utilisé est l'ESP D1 R32 et la branche utilisé est la branche GPIO25 
//On inclue les librairies
#include <Arduino.h>
#include <BluetoothSerial.h>

//On autorise le bluetooth et on défini la broche du signal
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define RELAY_PIN 25 // GPIO25 de l'ESP32 connecté à la broche IN du relais

//On défini la connexion bluetooth 
BluetoothSerial SerialBT;


void setup() {
  //On règle la connexion à 115200 bauds
  Serial.begin(115200);
  SerialBT.begin("ESP32_B2_Karim"); //Nom de l'ESP
  Serial.println(" Démarrage de l'ESP... Veuillez vous connectez en Bluetooth ");
  //On défini l'actionneur en sortie
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); 
  }
  delay(20);

  switch (RELAY_PIN) {

    case 0: //Si on envoie '0' l'actionneur n'est plus alimenté 
       Serial.write(SerialBT.read() == '0');
      digitalWrite(RELAY_PIN, LOW);
       delay(5000);
       break;

    case 1: //Si on envoie '1' l'actionneur est alimenté 
      Serial.write(SerialBT.read() == '1');
      digitalWrite(RELAY_PIN, HIGH);
      delay(5000);
      break;
   }
} 
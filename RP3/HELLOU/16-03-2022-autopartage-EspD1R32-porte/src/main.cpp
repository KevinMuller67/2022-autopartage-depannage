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
int valBT;

void setup() {
  //On règle la connexion à 115200 bauds
  Serial.begin(115200);
  SerialBT.begin("ESP32_B2_Karim"); //Nom de l'ESP
  Serial.println("L'ESP a démarré, vous pouvez le connecter en Bluetooth !");
  //On défini l'actionneur en sortie
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
   // Serial.write(SerialBT.read()); 
  //Si on envoie 'a' l'actionneur est alimenté 
       if (valBT == 1){
      digitalWrite(RELAY_PIN, HIGH);
       delay(5000);
      } 
  //Si on envoie 'b' l'actionneur n'est plus alimenté
      else if (valBT == 0){
      digitalWrite(RELAY_PIN, LOW);
      delay(5000);
       }
  
}
//On inclue les librairies
#include <Arduino.h>
#include <BluetoothSerial.h>

//On autorise le bluetooth et on défini la led a clignoter
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define LED_BUILTIN 2


BluetoothSerial SerialBT;


void setup() {
  //On règle la connexion à 115200 bauds
  Serial.begin(115200);
  SerialBT.begin("ESP32_B2_Jordan"); //Nom de l'ESP
  Serial.println("L'ESP a démarré, vous pouvez le connecter en bluetooth !");
  //On défini la led en sortie
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
 //Vérifie si il y a des données disponibles et lit les données reçus
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
  //Si on envoie 'a' la led s'allume et s'eteint
  if (SerialBT.read() == 'a'){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  }
}
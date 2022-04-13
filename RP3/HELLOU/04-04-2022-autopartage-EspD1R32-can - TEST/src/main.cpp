//Ce programme permet d'activer et désactiver l'actionneur en envoyant un caractère par Bluetooth
//'0' en bluetooth pour faire sortir l'actionneur (mode: vérouillé véhicule)
//'1' en bluetooth pour faire rentrer l'actionneur (mode: déverouillé véhicule)
//L'ESP utilisé est l'ESP D1 R32 et la broche utilisée est le GPIO25 

//On inclue les librairies
#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>
#include <BluetoothSerial.h>


//On autorise le bluetooth et on défini la broche du signal
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#define RELAY_PIN 25 // GPIO25 de l'ESP32 connecté à la broche IN de la carte relais

BluetoothSerial SerialBT; // On défini la connexion bluetooth 

CAN_device_t CAN_cfg;               // CAN Config
unsigned long previousMillis = 0;   // will store last time a CAN Message was send
const int interval = 1000;          // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;       // Receive Queue size

void setup() {
    Serial.begin(115200);
    Serial.println("Basic Demo - ESP32-Arduino-CAN");
    CAN_cfg.speed = CAN_SPEED_125KBPS;
    CAN_cfg.tx_pin_id = GPIO_NUM_4;
    CAN_cfg.rx_pin_id = GPIO_NUM_2;
    CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
    ESP32Can.CANInit(); // Init du module CAN

    SerialBT.begin("ESP32_B2_Karim"); // Nom de l'ESP
    Serial.println("L'ESP a démarré, vous pouvez le connecter en Bluetooth !");
    pinMode(RELAY_PIN, OUTPUT); // On défini l'actionneur en sortie
}

void FonctionPorte() //définition de la fonction
{
  int valBT = 0;
  if (SerialBT.available()) { //tester si une donnée est arrivée par Bluetooth
  valBT = SerialBT.read();}
  // Serial.write(SerialBT.read()); 

  //Si on envoie '1' l'actionneur est alimenté 
       if (valBT == '1'){
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("***************************** okay okay, le véhicule est déverouillé *****************************");
       delay(500);
      } 
  //Si on envoie '0' l'actionneur n'est plus alimenté
      else if (valBT == '0'){
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("***************************** okay okay, le véhicule est vérouillé *****************************");
      delay(500);
       }
}

void loop() {

    FonctionPorte(); //appel de la fonction

  /*--------------------PARTIE BUS CAN--------------------*/

    CAN_frame_t rx_frame;

  unsigned long currentMillis = millis();

  // Réception de la trame CANReceive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {

    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      printf("New standard frame");
    }
    else {
      printf("New extended frame");
    }

    if (rx_frame.MsgID == 0x300, rx_frame.FIR.B.DLC == 3 ) {
          printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        printf("0x%02X ", rx_frame.data.u8[i]);
      }
      printf("\n");
      // printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
    }/*
    else {
      printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        printf("0x%02X ", rx_frame.data.u8[i]);
      }
      printf("\n");
    }*/

    if (rx_frame.MsgID == 0x79) {
      printf(" allooo ");
      // printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
    }
  }
  // Envoi du message
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = 0x001;
    tx_frame.FIR.B.DLC = 8;
    tx_frame.data.u8[0] = 0x00;
    tx_frame.data.u8[1] = 0x01;
    tx_frame.data.u8[2] = 0x02;
    tx_frame.data.u8[3] = 0x03;
    tx_frame.data.u8[4] = 0x04;
    tx_frame.data.u8[5] = 0x05;
    tx_frame.data.u8[6] = 0x06;
    tx_frame.data.u8[7] = 0x07;
    ESP32Can.CANWriteFrame(&tx_frame);
  }
}
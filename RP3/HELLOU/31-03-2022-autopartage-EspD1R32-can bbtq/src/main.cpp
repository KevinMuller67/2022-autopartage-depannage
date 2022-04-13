//CetTE Application permet d'activer et désactiver l'actionneur en envoyant un caractère par Bluetooth
//'0' en bluetooth pour faire sortir l'actionneur (mode: vérouillé véhicule)
//'1' en bluetooth pour faire rentrer l'actionneur (mode: déverouillé véhicule)
//L'ESP utilisé est l'ESP D1 R32 et la broche utilisée est le GPIO25 

//On inclue les librairies
#include <ESP32CAN.h>
#include <CAN_config.h>
#include <LibPorte.h>


//On autorise le bluetooth et on défini la broche du signal
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
//#define RELAY_PIN 25 // GPIO25 de l'ESP32 connecté à la broche IN de la carte relais


CAN_device_t CAN_cfg;               // CAN Config
unsigned long previousMillis = 0;   // will store last time a CAN Message was send
const int interval = 1000;          // interval at which send CAN Messages (milliseconds)
const int rx_queue_size = 10;       // Receive Queue size

LibPorte libporte(25);

void setup() {
    Serial.begin(115200);
    CAN_cfg.speed = CAN_SPEED_125KBPS;
    CAN_cfg.tx_pin_id = GPIO_NUM_4;
    CAN_cfg.rx_pin_id = GPIO_NUM_2;
    CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
    ESP32Can.CANInit(); // Init CAN Module
}

void loop() {

    libporte.FonctionPorte(); //appel de la fonction

  /*--------------------PARTIE BUS CAN--------------------*/
    CAN_frame_t rx_frame;

  unsigned long currentMillis = millis();

  // Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) {

    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      printf("New standard frame");
    }
    else {
      printf("New extended frame");
    }

    if (rx_frame.FIR.B.RTR == CAN_RTR) {
      printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
    }
    else {
      printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        printf("0x%02X ", rx_frame.data.u8[i]);
      }
      printf("\n");
    }
  }
  // Send CAN Message
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
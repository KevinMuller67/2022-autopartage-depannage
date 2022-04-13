#ifndef LibPorte_H
#define LibPorte_H

#include <Arduino.h>
#include <BluetoothSerial.h>



//On défini la connexion bluetooth 

class LibPorte
{
    public: 
    LibPorte(int pin);
    void FonctionPorte();
    BluetoothSerial SerialBT;
    private:
    int _pin;

};

#endif

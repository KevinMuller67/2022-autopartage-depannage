#ifndef Porte_h
#define Porte_h

#include <Arduino.h>

class Porte
{
    private:
    int pinPorte;
    public:
    Porte(int pin);
    void Ferme();
    void Ouvre();
};

#endif

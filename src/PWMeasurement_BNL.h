#ifndef PWMEASUREMENT_BNL_H
#define PWMEASUREMENT_BNL_H

#include <Arduino.h>

class PWMeasurement_BNL{
    public:
        PWMeasurement_BNL(int pin);
        int getHigh();
        int getLow();
        int getPW();
    private:
        const int inputPin;
        int PWHigh = 0;
        int PWLow = 0;
        int PW = 0;

        void PCISR();
};

#endif
#ifndef PWMEASURE_BNL_H
#define PWMEASURE_BNL_H

#include <Arduino.h>

class PWMeasure_BNL{
    public:
        PWMeasure_BNL(int pin);
        int getHigh();
        int getLow();
        int getPulseWidth();

    private:
        const int inputPin;
        int PWHigh = 0;
        int PWLow = 0;
        int PW = 0;

        unsigned long whenStart = 0;
        unsigned long whenEnd = 0;
        unsigned long measure = 0;

        void handleInterrupt();
        static void PCISR();
        static PWMeasure_BNL* instance;
};

#endif
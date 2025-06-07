#ifndef PWMEASURE_BNL_H
#define PWMEASURE_BNL_H

#include <Arduino.h>

#define MAX_INSTANCES 24

class PWMeasure_BNL{
    public:
        PWMeasure_BNL(int pin);
        static void begin();

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
        static void callHandleInterrupt(int index);

        static void PCISR0();
        static void PCISR1();
        static void PCISR2();
        static void PCISR3();
        static void PCISR4();
        static void PCISR5();
        static void PCISR6();
        static void PCISR7();
        static void PCISR8();
        static void PCISR9();
        static void PCISR10();
        static void PCISR11();
        static void PCISR12();
        static void PCISR13();
        static void PCISR14();
        static void PCISR15();
        static void PCISR16();
        static void PCISR17();
        static void PCISR18();
        static void PCISR19();
        static void PCISR20();
        static void PCISR21();
        static void PCISR22();
        static void PCISR23();

        static void (*isrTable[MAX_INSTANCES])();
        static PWMeasure_BNL* instance[MAX_INSTANCES];

        static int count;
        const int idx;
};

#endif

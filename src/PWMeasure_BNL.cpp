#include "PWMeasure_BNL.h"
#include <PinChangeInterrupt.h>

PWMeasure_BNL* PWMeasure_BNL::instance[MAX_INSTANCES] = {nullptr};
void (*PWMeasure_BNL::isrTable[MAX_INSTANCES])() = {nullptr};
int PWMeasure_BNL::count = 0;

PWMeasure_BNL::PWMeasure_BNL(int pin)
     : inputPin(pin),
       idx(count < MAX_INSTANCES ? count : MAX_INSTANCES - 1) {
    if (count < MAX_INSTANCES) {
        instance[idx] = this;
        count++;
    }

    pinMode(inputPin, INPUT);
}

void PWMeasure_BNL::begin() {
    for (int i = 0; i < count; i++) {
        if (!isrTable[i]) {
            // populate the table with appropriate ISR
            switch (i) {
                case 0: isrTable[i] = PCISR0; break;
                case 1: isrTable[i] = PCISR1; break;
                case 2: isrTable[i] = PCISR2; break;
                case 3: isrTable[i] = PCISR3; break;
                case 4: isrTable[i] = PCISR4; break;
                case 5: isrTable[i] = PCISR5; break;
                case 6: isrTable[i] = PCISR6; break;
                case 7: isrTable[i] = PCISR7; break;
                case 8: isrTable[i] = PCISR8; break;
                case 9: isrTable[i] = PCISR9; break;
                case 10: isrTable[i] = PCISR10; break;
                case 11: isrTable[i] = PCISR11; break;
                case 12: isrTable[i] = PCISR12; break;
                case 13: isrTable[i] = PCISR13; break;
                case 14: isrTable[i] = PCISR14; break;
                case 15: isrTable[i] = PCISR15; break;
                case 16: isrTable[i] = PCISR16; break;
                case 17: isrTable[i] = PCISR17; break;
                case 18: isrTable[i] = PCISR18; break;
                case 19: isrTable[i] = PCISR19; break;
                case 20: isrTable[i] = PCISR20; break;
                case 21: isrTable[i] = PCISR21; break;
                case 22: isrTable[i] = PCISR22; break;
                case 23: isrTable[i] = PCISR23; break;
            }
        }
        attachPinChangeInterrupt(instance[i]->inputPin, isrTable[i], CHANGE);
    }
}

int PWMeasure_BNL::getHigh() {
    return PWHigh;
}

int PWMeasure_BNL::getLow() {
    return PWLow;
}

int PWMeasure_BNL::getPulseWidth() {
    return PW;
}

void PWMeasure_BNL::handleInterrupt() {
    whenStart = micros();
    measure = whenStart - whenEnd;
    if (digitalRead(inputPin) == HIGH) {
        PWHigh = measure;
    } else {
        PWLow = measure;
    }
    PW = PWHigh + PWLow;
    whenEnd = whenStart;
}

void PWMeasure_BNL::callHandleInterrupt(int index) {
    if (index < MAX_INSTANCES && instance[index]) {
        instance[index]->handleInterrupt();
    }
}

#define DEFINE_PCISR(num) \
    void PWMeasure_BNL::PCISR##num() { callHandleInterrupt(num); }

DEFINE_PCISR(0)  DEFINE_PCISR(1)  DEFINE_PCISR(2)  DEFINE_PCISR(3)
DEFINE_PCISR(4)  DEFINE_PCISR(5)  DEFINE_PCISR(6)  DEFINE_PCISR(7)
DEFINE_PCISR(8)  DEFINE_PCISR(9)  DEFINE_PCISR(10) DEFINE_PCISR(11)
DEFINE_PCISR(12) DEFINE_PCISR(13) DEFINE_PCISR(14) DEFINE_PCISR(15)
DEFINE_PCISR(16) DEFINE_PCISR(17) DEFINE_PCISR(18) DEFINE_PCISR(19)
DEFINE_PCISR(20) DEFINE_PCISR(21) DEFINE_PCISR(22) DEFINE_PCISR(23)

#include "PWMeasure_BNL.h"
#include <PinChangeInterrupt.h>

int PWMeasure_BNL::count = 0;

PWMeasure_BNL::PWMeasure_BNL(int pin)
     : inputPin(pin),
       idx(count) {
    instance[idx] = this;
    count++;

    pinMode(inputPin, INPUT);
}

void PWMeasure_BNL::begin() {
    for (int i = 0; i < count; i++) {
        attachPinChangeInterrupt(instance[i]->inputPin, PCISR, CHANGE);
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

void PWMeasure_BNL::PCISR() {
    instance->handleInterrupt();
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
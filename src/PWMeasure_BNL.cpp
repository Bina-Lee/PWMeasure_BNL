#include "PWMeasure_BNL.h"
#include <PinChangeInterrupt.h>

PWMeasure_BNL* PWMeasure_BNL::instance = nullptr;

PWMeasure_BNL::PWMeasure_BNL(int pin) : inputPin(pin) {
    pinMode(inputPin, INPUT);
    instance = this;
    attachPCINT(digitalPinToPCINT(inputPin), PCISR, CHANGE);
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
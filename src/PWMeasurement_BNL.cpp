#include "PWMeasurement_BNL.h"
#include <PinChangeInterrupt.h>

PWMeasurement_BNL::PWMeasurement_BNL(int pin) : inputPin(pin) {
    pinMode(inputPin, INPUT);
    attachPCINT(digitalPinToPCINT(inputPin), PCISR, CHANGE);
}

int PWMeasurement_BNL::getHigh() {
    return PWHigh;
}

int PWMeasurement_BNL::getLow() {
    return PWLow;
}

int PWMeasurement_BNL::getPulseWidth() {
    return PW;
}

void PWMeasurement_BNL::PCISR() {
    whenStart = micros();
    measure = whenStart - whenEnd;
    if (digitalRead(inputPin) == HIGH) {
        PWHigh = measure;
    } else {
        PWLow = measure;
    }
    PW = PWHigh + PWLow;
    whenEnd = whenStart
}
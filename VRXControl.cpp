#include "VRXControl.h"

volatile unsigned long pulseCount = 0;
unsigned long lastPulseTime = 0;

void countPulse()
{
    unsigned long currentTime = micros();
    
    // Debounce: ignore pulses that come too quickly (< 10 microseconds)
    if (currentTime - lastPulseTime > 10) {
        pulseCount++;
        lastPulseTime = currentTime;
    }
}

VRXControl::VRXControl(VRXControlPins pins)
{
    _pins = pins;

    pinMode(_pins.S1_PIN, OUTPUT);
    pinMode(_pins.S2_PIN, OUTPUT);
    pinMode(_pins.S3_PIN, OUTPUT);
    pinMode(_pins.CS1_PIN, OUTPUT);
    pinMode(_pins.CS2_PIN, OUTPUT);
    pinMode(_pins.CS3_PIN, OUTPUT);

    pinMode(_pins.VIDEO_DET_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(_pins.VIDEO_DET_PIN), countPulse, FALLING);

    digitalWrite(_pins.S1_PIN, LOW);
    digitalWrite(_pins.S2_PIN, LOW);
    digitalWrite(_pins.S3_PIN, LOW);
    digitalWrite(_pins.CS1_PIN, LOW);
    digitalWrite(_pins.CS2_PIN, LOW);
    digitalWrite(_pins.CS3_PIN, LOW);
}

bool VRXControl::detectVideo()
{
    pulseCount = 0;
    delay(100);
    unsigned long count = pulseCount;
    Serial.print("Pulse count: ");
    Serial.println(count);
    return (count > _pins.THRESHOLD);
}

void VRXControl::setChannel(const ChEntry &ch)
{
    digitalWrite(_pins.S1_PIN, ch.s1? HIGH : LOW);
    digitalWrite(_pins.S2_PIN, ch.s2? HIGH : LOW);
    digitalWrite(_pins.S3_PIN, ch.s3? HIGH : LOW);

    digitalWrite(_pins.CS1_PIN, ch.cs1 ? HIGH : LOW);
    digitalWrite(_pins.CS2_PIN, ch.cs2 ? HIGH : LOW);
    digitalWrite(_pins.CS3_PIN, ch.cs3 ? HIGH : LOW);

    delay(_pins.CHANNEL_SETTLE_MS);
}
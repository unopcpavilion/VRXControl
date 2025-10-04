#include <Arduino.h>

void waitForInMs(unsigned int ms);

struct VRXControlPins
{
    uint8_t S1_PIN, S2_PIN, S3_PIN, CS1_PIN, CS2_PIN, CS3_PIN, VIDEO_DET_PIN;
    unsigned long THRESHOLD, CHANNEL_SETTLE_MS;
};

class VRXControl
{
private:
    VRXControlPins _pins;

public:
    VRXControl(VRXControlPins pins);

    bool detectVideo();
    void setChannel(const struct ChEntry &ch);
};

struct ChEntry
{
    uint8_t cs1, cs2, cs3;
    uint8_t s1, s2, s3;
    uint16_t freq; // MHz
};

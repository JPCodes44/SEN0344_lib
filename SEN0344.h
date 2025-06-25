#ifndef MySensorLib_h
#define MySensorLib_h

#include "Arduino.h"
#include <Wire.h>

class SEN0344
{
public:
    SEN0344(uint8_t SEN0344_ID);
    bool begin();
    float readSpo2();

private:
    uint8_t sensor_ID;
    void i2c_write(uint8_t addr, uint8_t byte, uint8_t deviceID);
    uint8_t i2c_read(uint8_t addr, uint8_t deviceID);
};

#endif // MySensorLib_h

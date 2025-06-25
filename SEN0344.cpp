#include "SEN0344.h"

SEN0344::SEN0344(uint8_t SEN0344_ID)
{
    sensor_ID = SEN0344_ID; // Can either be 0x47 or 0x48
}

struct Spo2Sample
{
    uint32_t red;
    uint32_t ir;
};

bool SEN0344::begin()
{
    Wire.beginTransmission(sensor_ID);
    i2c_write(0x08, i2c_read(0x08, sensor_ID) | 0b00010000, sensor_ID); // Set the FFIO configuration (FIFO_ROLLOVER_EN (bit4=1)) to overwrite oldest data with newer ones for continuous streaming data
    i2c_write(0x09, 0b00000011, sensor_ID);                             // Set Mode control to SpO2 Mode and Red and IR active LED
    i2c_write(0x0A, 0b00011100, sensor_ID);
    return true; // allows the sensor to read 3200 samples per second
}

float SEN0344::readSpo2()
{
    Spo2Sample sample = {0, 0};
    Wire.beginTransmission(sensor_ID);
    Wire.write(0x07); // Set register to FIFO read register
    Wire.endTransmission(false);
    Wire.requestFrom(sensor_ID, 6);

    if (Wire.available() == 6)
    {
        // Read Red channel (first triplet)
        sample.red = (uint32_t)(Wire.read() | Wire.read() << 8 | Wire.read() << 16);

        // Read IR channel (second triplet)
        sample.ir = (uint32_t)(Wire.read() | Wire.read() << 8 | Wire.read() << 16);
        return (float)sample.red / (float)sample.ir;
    }
    else
        return 0.0;
}

/****************************************************************************/

void SEN0344::i2c_write(uint8_t addr, uint8_t byte, uint8_t deviceID)
{
    Wire.beginTransmission(deviceID);
    Wire.write(addr);
    Wire.write(byte);
    Wire.endTransmission();
}

uint8_t SEN0344::i2c_read(uint8_t addr, uint8_t deviceID)
{
    Wire.beginTransmission(deviceID); // Begin I2C transmission to the device with the given ID
    Wire.write(addr);                 // Write the address from which we want to read
    Wire.endTransmission(false);      // End the transmission but keep the connection active
    Wire.requestFrom(deviceID, 1);    // Request 1 byte of data from the device
    if (Wire.available() == 1)        // Check if the device has sent the requested byte
        return Wire.read();           // Read and return the byte
    else
        return 0xFF; // Return 0xFF if no data is available
}

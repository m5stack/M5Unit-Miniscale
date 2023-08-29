#ifndef _UNIT_SCALES_H_
#define _UNIT_SCALES_H_

#include <Arduino.h>
#include <Wire.h>

// I2C
#define DEVICE_DEFAULT_ADDR 0x26

// SCALES REGISTER
#define UNIT_SCALES_RAW_ADC_REG     0x00
#define UNIT_SCALES_CAL_DATA_REG    0x10
#define UNIT_SCALES_BUTTON_REG      0x20
#define UNIT_SCALES_RGB_LED_REG     0x30
#define UNIT_SCALES_SET_GAP_REG     0x40
#define UNIT_SCALES_SET_OFFESET_REG 0x50
#define JUMP_TO_BOOTLOADER_REG      0xFD
#define FIRMWARE_VERSION_REG        0xFE
#define I2C_ADDRESS_REG             0xFF

class UNIT_SCALES {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
    bool writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    bool readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t sda = 21, uint8_t scl = 22,
               uint8_t addr = DEVICE_DEFAULT_ADDR);
    // SCALES
    int32_t getRawADC();
    float getWeight();
    float getGapValue();
    void setGapValue(float offset);
    void setOffset(void);
    // RGB LED CTL
    // uint8_t status();
    bool setLEDColor(uint32_t color);
    uint32_t getLEDColor();
    // BUTTON
    uint8_t getBtnStatus();
    uint8_t getFirmwareVersion(void);
    void jumpBootloader(void);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
};

#endif

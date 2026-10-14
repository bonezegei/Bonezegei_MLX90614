/*
  Bonezegei_MLX90614.h
  Arduino Library for MLX90614 Contactless Infrared Temperature Sensor
  Author: Bonezegei (Jofel Batutay)
  Date: October 14, 2026
*/

#ifndef _BONEZEGEI_MLX90614_H_
#define _BONEZEGEI_MLX90614_H_

#include <Arduino.h>
#include <Wire.h>

#define MLX90614_I2CADDR    0x5A

#define MLX90614_RAW_TA     0x06
#define MLX90614_RAW_TOBJ1  0x07
#define MLX90614_RAW_TOBJ2  0x08

class Bonezegei_MLX90614 {
public:
  Bonezegei_MLX90614(uint8_t addr = MLX90614_I2CADDR);

  bool begin(TwoWire &wirePort = Wire);
  uint16_t readRaw(uint8_t reg);

  float readAmbientCelsius();
  float readAmbientFahrenheit();
  float readObjectCelsius();
  float readObjectFahrenheit();

  // Alias helper methods
  float getAmbientC();
  float getAmbientF();
  float getObjectC();
  float getObjectF();

private:
  uint8_t _addr;
  TwoWire *_wire;
};

#endif
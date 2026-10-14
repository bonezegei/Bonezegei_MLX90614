/*
  Bonezegei_MLX90614.cpp
  Arduino Library for MLX90614 Contactless Infrared Temperature Sensor
  Author: Bonezegei (Jofel Batutay)
  Date: October 14, 2026
*/

#include "Bonezegei_MLX90614.h"

Bonezegei_MLX90614::Bonezegei_MLX90614(uint8_t addr) {
  _addr = addr;
  _wire = &Wire;
}

bool Bonezegei_MLX90614::begin(TwoWire &wirePort) {
  _wire = &wirePort;
  _wire->begin();

  uint16_t raw = readRaw(MLX90614_RAW_TA);
  return (raw != 0xFFFF && raw != 0x0000);
}

uint16_t Bonezegei_MLX90614::readRaw(uint8_t reg) {
  _wire->beginTransmission(_addr);
  _wire->write(reg);

  if (_wire->endTransmission(false) != 0) {
    return 0xFFFF;
  }

  // Request 3 bytes: Data LSB, Data MSB, and PEC (Packet Error Code)
  if (_wire->requestFrom(_addr, (uint8_t)3) != 3) {
    return 0xFFFF;
  }

  uint8_t lsb = _wire->read();
  uint8_t msb = _wire->read();
  uint8_t pec = _wire->read();
  (void)pec; // Flush PEC byte

  uint16_t raw = ((uint16_t)msb << 8) | lsb;
  return raw;
}

float Bonezegei_MLX90614::readAmbientCelsius() {
  uint16_t raw = readRaw(MLX90614_RAW_TA);
  if (raw == 0xFFFF) return NAN;
  return (raw * 0.02f) - 273.15f;
}

float Bonezegei_MLX90614::readAmbientFahrenheit() {
  float tempC = readAmbientCelsius();
  if (isnan(tempC)) return NAN;
  return (tempC * 1.8f) + 32.0f;
}

float Bonezegei_MLX90614::readObjectCelsius() {
  uint16_t raw = readRaw(MLX90614_RAW_TOBJ1);
  if (raw == 0xFFFF) return NAN;
  return (raw * 0.02f) - 273.15f;
}

float Bonezegei_MLX90614::readObjectFahrenheit() {
  float tempC = readObjectCelsius();
  if (isnan(tempC)) return NAN;
  return (tempC * 1.8f) + 32.0f;
}

float Bonezegei_MLX90614::getAmbientC() {
  return readAmbientCelsius();
}

float Bonezegei_MLX90614::getAmbientF() {
  return readAmbientFahrenheit();
}

float Bonezegei_MLX90614::getObjectC() {
  return readObjectCelsius();
}

float Bonezegei_MLX90614::getObjectF() {
  return readObjectFahrenheit();
}
// https://docs.arduino.cc/tutorials/mkr-wifi-1010/mkr-jlink-setup/
// Mock out the Serial class so we can attempt to figure out what is going wrong.
#ifndef MOCKSERIAL_H
#define MOCKSERIAL_H

#include <stdint.h>
#include "Arduino.h"

#define SERIAL_BUS getGlobalMockSerial()

class MockSerial {
public:
  void begin(unsigned long baudRate) {
    Serial.print("baudRate=");
    Serial.println(baudRate);
  }

  void setData(uint8_t *data) {
    _data = data;
  }

  size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length) {
    size_t sz = 0;
    for (int i = 0; i < length; i++) {
      if (_data[i] == terminator) {
        break;
      }
      buffer[i] = _data[i];
      sz++;
    }
    return sz;
  }

  size_t available() {
    return sizeof(_data);
  }

private:
  uint8_t *_data;
};

MockSerial& getGlobalMockSerial()
{
  static MockSerial ms;
  return ms;
}

#endif
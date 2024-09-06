#include <Arduino.h>
#include "RrFirmware.h"

// https://docs.arduino.cc/tutorials/mkr-wifi-1010/mkr-jlink-setup/

#define BUFSZ 101
#define MAX_SZ (BUFSZ - 1)

rrfw::Isr isr;

// Mock out the Serial class so we can attempt to figure out what is going wrong.
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

#define SERIAL_BUS mockSerial

MockSerial mockSerial;
uint8_t *_buf;
void setup() {
  SerialUSB.begin(9600);

  _buf = reinterpret_cast<uint8_t *>(calloc(BUFSZ, sizeof(uint8_t)));
}

 rrfw::RrOpStorage recieve() {
  uint8_t *data;
  size_t sz;
  bzero(_buf, BUFSZ);
  if (SERIAL_BUS.available()) {
    sz = SERIAL_BUS.readBytesUntil('\n', _buf, BUFSZ);
  } 

  if (sz > MAX_SZ) {
    uint8_t data[]{};
    return rrfw::RrOpStorage(rrfw::RR_IO_RES_UNSUPPORTED, 0, data);
  }
  if (sz > 0) {
    data = reinterpret_cast<uint8_t *>(calloc(sz, sizeof(uint8_t)));
    memcpy(data, _buf, sz + 1);
  }
  return isr.deserialize(data, sz);
}

void loop() {
  delay(5000);

  Serial.println("program started");

  uint8_t *testData = reinterpret_cast<uint8_t *>(calloc(3, sizeof(uint8_t)));
  testData[0] = rrfw::RR_CMD_U5;
  testData[1] = 1;
  testData[2] = 0x033;
  testData[3] = '\n';

  SerialUSB.println("setting test data");
  mockSerial.setData(testData);

  SerialUSB.println("reading data");
  const rrfw::RrOpStorage rx = recieve();
  SerialUSB.println("data received");



  SerialUSB.print("CMD: ");
  SerialUSB.println(static_cast<int>(rx._cmd));

  SerialUSB.print("SZ: ");
  SerialUSB.println(static_cast<int>(rx._sz));

  SerialUSB.print("Data: '");
  SerialUSB.println("'");
  SerialUSB.println("finished");

  while (1)
    ;
}

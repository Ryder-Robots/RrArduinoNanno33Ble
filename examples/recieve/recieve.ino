// https://docs.arduino.cc/tutorials/mkr-wifi-1010/mkr-jlink-setup/
// Mock out the Serial class so we can attempt to figure out what is going wrong.
#include "MockSerial.h"
#include "RrFirmware.h"

rrfw::Isr isr;
uint8_t *_buf;
void setup() {
  SerialUSB.begin(9600);

  _buf = reinterpret_cast<uint8_t *>(calloc(BUFSZ, sizeof(uint8_t)));
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
  SERIAL_BUS.setData(testData);

  SerialUSB.println("reading data");
  rrfw::RrOpStorage rx(rrfw::RR_IO_RES_NOTREADY, 0, {});
  isr.recieve(rx);
  SerialUSB.println("data received");

  SerialUSB.print("CMD: ");
  SerialUSB.println(static_cast<int>(rx._cmd));

  SerialUSB.print("SZ: ");
  SerialUSB.println(static_cast<int>(rx._sz));

  SerialUSB.print("Data: '");
  SerialUSB.println("'");
  SerialUSB.println("finished");


  // Test 2
  testData[0] = '\n';
  SERIAL_BUS.setData(testData);
  size_t r = isr.recieve(rx);
  SerialUSB.print("return data is:");
  SerialUSB.println(r);

  if (rx._cmd == rrfw::RR_IO_RES_NOTREADY) {
    SerialUSB.println("test success!");
  } else {
    SerialUSB.println("failed!");
  }

  while (1)
    ;
}

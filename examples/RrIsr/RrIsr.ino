#include <RrFirmware.h>
#include <TestFrameWork.h>

void setup() 
{

}


void loop() 
{
  delay(2000);
  uint8_t data[] = {rrfw::RR_CMD_U1, 4, 3, 5, 10, 8};
  rrfw::Isr isr = rrfw::Isr();
  rrfw::RrOpStorage op = isr.deserialize(data, 4 + 2);

  rrfwtest::assertEquals(rrfw::RR_CMD_U1, op._cmd, "test command is correct");
  rrfwtest::assertEquals(4,  op._sz, "test deserialize size");
  rrfwtest::assertEquals(3,  op._data[0], "test deserialize data 1");
  rrfwtest::assertEquals(5,  op._data[1], "test deserialize data 2");
  rrfwtest::assertEquals(10, op._data[2], "test deserialize data 3");
  rrfwtest::assertEquals(8,  op._data[3], "test deserialize data 4");

  const uint8_t *result = isr.serialize(op);
  rrfwtest::assertEquals(rrfw::RR_CMD_U1, result[0], "test command is correct");
  rrfwtest::assertEquals(4,  result[1], "test serialize size");
  rrfwtest::assertEquals(3,  result[2], "test serialize data 1");
  rrfwtest::assertEquals(5,  result[3], "test serialize data 2");
  rrfwtest::assertEquals(10, result[4], "test serialize data 3");
  rrfwtest::assertEquals(8,  result[5], "test serialize data 4");

  while(1);
}

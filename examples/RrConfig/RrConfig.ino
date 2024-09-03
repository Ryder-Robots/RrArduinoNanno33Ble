#include <RrFirmware.h>
#include <TestFrameWork.h>

void setup() 
{
  delay(2000);
}

void loop() 
{
  delay(2000);
  rrfw::RrConfig conf = rrfw::RrConfig();
  rrfw::OpElCnt *op = conf.get_op(rrfw::RR_CMD_U1);

  rrfwtest::assertEquals(rrfw::RR_CMD_U1, op->_cmd_id, "test configuration cmd");

  while(1);
}
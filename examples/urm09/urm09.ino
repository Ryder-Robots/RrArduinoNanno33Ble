#include <RrFirmware.h>
#include <TestFrameWork.h>
#include <RrIsr.h>

rrfw::RrConfig conf = rrfw::RrConfig();
rrfw::Isr isr =  rrfw::Isr();

void setup()
{
  // Set USB board rate
  isr.begin(9600);

  // Perform Pre-Flight checks
  conf.begin(isr);
  Serial.println("Started");
  delay(2000);
}

void loop()
{


  delay(2000);
  Serial.println("Starting ultrasonic");

  const rrfw::RrOpStorage req = rrfw::RrOpStorage(rrfw::RR_CMD_U9, 0, {});
  const rrfw::OpElCnt *op = conf.get_op(static_cast<rrfw::RR_CMD>(req._cmd));

  for (int i = 0; i < 10; i++)
  {
    for (rrfw::RR_CMD cmd : {rrfw::RR_CMD_U8, rrfw::RR_CMD_U9})
    {
      Serial.print("testing :");
      Serial.println(cmd, HEX);

      const rrfw::RrOpStorage req = rrfw::RrOpStorage(cmd, 0, {});
      const rrfw::OpElCnt *op = conf.get_op(static_cast<rrfw::RR_CMD>(req._cmd));

      const rrfw::RrOpStorage res = op->_op->execute(req);
      isr.transmit(res);
      Serial.println("finish executing ultrasonic");
      float *data_res = reinterpret_cast<float *>(res._data);

      Serial.print("distance:");
      Serial.print(data_res[0]);
      Serial.println("cm");

      Serial.print("temprature:");
      Serial.print(data_res[1]);
      Serial.println(" C");
      delay(1000);
      Serial.print("\n");
    }
  }

  while (1)
    ;
}

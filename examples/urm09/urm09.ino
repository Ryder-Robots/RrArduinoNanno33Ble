#include <RrFirmware.h>
#include <TestFrameWork.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");
  delay(2000);
}

void loop() {
  delay(2000);
  Serial.println("Starting ultrasonic");
  rrfw::RrConfig conf = rrfw::RrConfig();
  const rrfw::RrOpStorage req = rrfw::RrOpStorage(rrfw::RR_CMD_U8, 0, {});
  const rrfw::OpElCnt *op = conf.get_op(static_cast<rrfw::RR_CMD>(req._cmd));

  for (int i = 0; i < 10; i++) {
    const rrfw::RrOpStorage res = op->_op->execute(req);
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

  while(1);
}

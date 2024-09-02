#include <RrFirmware.h>
#include <TestFrameWork.h>

void setup() 
{
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Started");
    delay(2000);
}

void loop() 
{
    delay(2000);
    Serial.println("Starting Accelometer");
    rrfw::RrConfig conf = rrfw::RrConfig();
    const rrfw::RrOpStorage req = rrfw::RrOpStorage(rrfw::RR_CMD_U6, 0, {});
    const rrfw::OpElCnt *op = conf.get_op(static_cast<rrfw::RR_CMD>(req._cmd));

    for(int i =0; i < 10; i++) {
          const rrfw::RrOpStorage res = op->_op->execute(req);
          Serial.println("finish executing accelerometer");
          float *data_res = reinterpret_cast<float *>(res._data);
          Serial.print("sample rate:");
          Serial.println(data_res[0]);
          Serial.print("x:");
          Serial.println(data_res[1]); 
          Serial.print("y:");
          Serial.println(data_res[2]);
          Serial.print("z:");
          Serial.println(data_res[3]);
          delay(1000);
          Serial.print("\n");
    }
}
#include "RrOpStorage.h"
void setup() 
{
  uint8_t data[] = {};
  rrfw::RrOpStorage rr = rrfw::RrOpStorage(RR_CMD_U1, 0, data);
  delay(2000);

  for (int i = 0; i < 20; i++) {
    Serial.print("CMD =");
    Serial.println(rr._cmd);
    delay(1000);
  }
}


void loop() {}
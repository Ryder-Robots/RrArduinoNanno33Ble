/*!
 * Operate drone functions,  and pass the results to FAT Controller.
 */

#include <arduino-timer.h>
#include "RrFirmware.h"

#define BOARD_RATE 19200

using namespace rrfw;

// Global variables
Isr isr = Isr();
RrConfig conf = RrConfig();
Timer<1, micros> timer;
RrOpStorage rx(rrfw::RR_IO_RES_NOTREADY, 0, {});

// Send this action to indicate competion.
RrOpStorage complete(RR_IO_COM_COMPLETE, 0, {});

/*!
 * @fn observations()
 & @brief iterate through observations,  if the fat controller is ready, send them.
 */
bool observations(void *)
{
  // for (RR_CMD cmd : {RR_CMD_U5, RR_CMD_U6, RR_CMD_U7, RR_CMD_U8, RR_CMD_U9, RR_CMD_UA, RR_CMD_UB})
  for (RR_CMD cmd : {RR_CMD_U5, RR_CMD_U6, RR_CMD_U7, RR_CMD_U8, RR_CMD_U9})
  {
    const rrfw::RrOpStorage req = rrfw::RrOpStorage(cmd, 0, {});
    const rrfw::OpElCnt *op = conf.get_op(static_cast<rrfw::RR_CMD>(req._cmd));
    const rrfw::RrOpStorage res = op->_op->execute(req);

    // TODO: this should be a blocking loop that waits for the Fat controller to become ready.
    isr.recieve(rx);
    if (rx._cmd == RR_IO_COM_READY)
    {
      isr.transmit(res);
    }
  }
  isr.transmit(complete);
  return true;
}

/*!
 * @fn actions
 * @brief perform action.
 */
bool actions(void *)
{
}

void setup()
{
  // put your setup code here, to run once:
  isr.begin(BOARD_RATE);
  conf.begin(isr);
  delay(2000);

  // Wait for Fat Controller
  while (rx._cmd != rrfw::RR_IO_COM_READY)
  {
    isr.recieve(rx);
  }

  // setup complete, ready to start processing.
  float *res = reinterpret_cast<float *>(calloc(2, sizeof(float)));
  res[0] = static_cast<float>(RR_CMD_U5);
  res[1] = 0;
  size_t rsz = (2 * sizeof(float));
  const RrOpStorage tx = RrOpStorage(RR_IO_RES_READY, rsz, reinterpret_cast<uint8_t *>(res));
  timer.every(1000, observations);
  isr.transmit(tx);
}

void loop()
{
  timer.tick();

  // Check for inbound actions, and perform each one.
}

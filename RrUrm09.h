/*!
 * Ryder Robots Shared Micro-Processor
 * Copyright (C) 2024  Ryder Robots
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * =====================================================================
 *
 * Header file for DF Robot URM09 ultrasonic sensor.
 *
 * data is [dist:float, temp: float]
 */

#ifndef RRURM09_H
#define RRURM09_H

#include "DFRobot_URM09.h"
#include "RrIsr.h"
#include "RrOpBase.h"

namespace rrfw {
class RrUrm09 : public RrOpBase {
   public:
   /*!
    * @fn RrUrm
    * @brief class constructor
    * @param addr I2C address
    * @param cmd  RrOpStorage ID associated with this interface
    * @param isr  Interface to ISR object
    * @param measureMode mode to explain how distance is to be measured
    * @param measureRange the maximum range of sensor in centermeters
    */
    RrUrm09(uint8_t addr, uint8_t cmd, Isr& isr, uint8_t measureMode = MEASURE_MODE_AUTOMATIC,
            uint8_t measureRange = MEASURE_RANG_500);

    /*!
     * @fn ~RrUrm09
     * @brief class deconstructor
     */
    ~RrUrm09() {}

    /*!
     * @fn execute 
     * 
     * @brief uses active mode to send and ping and recieve an echo,  will also return temprature
     * the returning RrOpStorage object will have a bytes array that will be in the following 
     * format: {float, float} where the first element is distance in centermeters, and the
     * second element is temprature in degrees celsius.
     * 
     * @param bytes inbound request
     * 
     * @return RrOpStorage object populated as described in brief.
     */
    const RrOpStorage execute(const RrOpStorage bytes) override;

    /*!
     * @fn available
     * @brief indicates that sensor is availabl,  note that FIFO is not used for this 
     * sensor.
     * @return any value above 0 indicates sensor is ready.
     */
    int available() override;

   private:
    // Keep each instance containerised, to avoid conflicts.
    DFRobot_URM09 _urm = DFRobot_URM09();
    uint8_t _addr;
    uint8_t _measureMode;
    uint8_t _measureRange;
    float* _res;
    Isr _isr;
};
}  // namespace rrfw

#endif
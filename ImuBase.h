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
 * Base class for IMU chip base.
 *
 * data returned as {sampleRate:float, x:float, y:float, z:float}
 */

#ifndef IMUBASE_H
#define IMUBASE_H

#include "Arduino_BMI270_BMM150.h"
#include "RrIsr.h"
#include "RrOpBase.h"

namespace rrfw {

class ImuBase : public RrOpBase {
   public:
    /*!
     * @fn ImuBase
     * @brief class constructor
     * @return class object
     */
    ImuBase(BoschSensorClass imu, Isr isr)
        : _imu{imu}, _isr{isr}, _res{reinterpret_cast<float*>(calloc(4, sizeof(float)))} {}

    /*!
     * @fn execute
     * @brief performs execution for IMU sensor (inbuild on nano BLE)
     * @return for most sensors data will be float x, float y, float z (specifics on sensor)
     */
    const RrOpStorage execute(const RrOpStorage bytes) override;

    /*!
     * @fn available
     * @brief Number of samples in the FIFO.
     * @return number of samples
     */
    virtual int available() override {}

   protected:
    /*!
     * @fn sampleRate
     * @brief Sampling rate of the sensor.
     * @return sample rate in Hertz
     */
    virtual float sampleRate() {}

    /*!
     * @fn Results are in degrees/second.
     * @param x x vertice on cartesian plane
     * @param y y vertice on cartesian plane
     * @param z z verice on cartesian plane
     * @return Note that X, Y, and Z will be set (referenced).
     */
    virtual int read(float& x, float& y, float& z) {}

    BoschSensorClass _imu;  // IMY object
    float* _res;            // internal variable for results
    Isr _isr;
};
}  // namespace rrfw

#endif
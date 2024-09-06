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
 * Interface for magnretometer.  Gives compass points in three dimensions.
 */

#ifndef RRMAGNETOMETER_H
#define RRMAGNETOMETER_H

#include "ImuBase.h"

namespace rrfw {
class RrMagnetoMeter : public ImuBase {
   public:
    /*!
     * @fn RrMagnetoMeter
     * @brief class constructor
     * @param imu EMBED IMU interface
     * @param isr ISR interface
     */
    RrMagnetoMeter(BoschSensorClass imu, Isr isr) : ImuBase(imu, isr) {}

    /*!
     * @fn class deconstructor
     */
    ~RrMagnetoMeter() {}

    /*!
     * @fn available()
     * @brief Number of samples in the FIFO.
     * @return number of samples in FIFO
     */
    int available() override { return _imu.magneticFieldAvailable(); }

    /*!
     * @fn sampleRate()
     * @brief sampling rate in HZ for sensor
     * @return sample rate
     */
    float sampleRate() override { return _imu.magneticFieldSampleRate(); }

    /*!
     * @fn read
     * @brief populate X, Y, and Z coordinate for currently dertected magnetic field.
     * @param x float to populate for X coordinate
     * @param y float to populate for Y coordinate
     * @param z float to populate for Z coordinate
     * @return 
     */
    int read(float &x, float &y, float &z) override { return _imu.readMagneticField(x, y, z); }
};
}  // namespace rrfw

#endif //RRMAGNETOMETER_H
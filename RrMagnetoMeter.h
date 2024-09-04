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

#ifndef RRMAGNETOMETER
#define RRMAGNETOMETER

#include "ImuBase.h"

namespace rrfw
{
    class RrMagnetoMeter : public ImuBase {
    public:
        RrMagnetoMeter(BoschSensorClass imu, Isr isr) : ImuBase(imu, isr) {}
        
        ~RrMagnetoMeter() {}

        // Number of samples in the FIFO.
        int available() override
        {
            return _imu.magneticFieldAvailable();
        }

        // Sampling rate of the sensor.
        float sampleRate() override
        {
            return _imu.magneticFieldSampleRate();
        }

        // read from sensor
        int read(float &x, float &y, float &z) override
        {
            return _imu.readMagneticField(x, y, z);
        }
    };
}

#endif
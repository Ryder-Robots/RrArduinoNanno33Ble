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
 * Base class for IMU chip base 
 */

#ifndef IMUBASE_H
#define IMUBASE_H

#include "RrOpBase.h"
#include "Arduino_BMI270_BMM150.h"

namespace rrfw {

    class ImuBase : public RrOpBase {
    public:
        ImuBase(BoschSensorClass imu): 
            _imu{imu}, 
            _res{reinterpret_cast<float *>(calloc(4, sizeof(float)))}
        {}

        const RrOpStorage execute(const RrOpStorage  bytes) override;
        virtual int    available() {}  // Number of samples in the FIFO.
        virtual float  sampleRate() {} // Sampling rate of the sensor.
        virtual int    read(float& x, float& y, float& z) {} // Results are in degrees/second.

    protected:
        BoschSensorClass _imu;
        float*           _res;
    };
}

#endif
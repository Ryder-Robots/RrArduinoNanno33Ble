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
 * Interface for Accelerometer
 */

#ifndef RROPACCELEROMETER_H
#define RROPACCELEROMETER_H

#include <stdlib.h>
#include "Arduino_BMI270_BMM150.h"
#include "RrOpBase.h"

namespace rrfw {
    class RrOpAccelerometer : public RrOpBase {
        public:
            RrOpAccelerometer(BoschSensorClass imu): _imu{imu} {}
            ~RrOpAccelerometer() {}
            const RrOpStorage execute(const RrOpStorage  bytes) override;
        private:
            BoschSensorClass _imu;
    };
}

#endif
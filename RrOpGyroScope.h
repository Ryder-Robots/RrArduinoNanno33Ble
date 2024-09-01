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
 * Interface for gyroscop.
 */


#include "RrOpBase.h"

#ifndef RROPGYROSCOPE
#define RROPGYROSCOPE

#include <stdlib.h>
#include "Arduino_BMI270_BMM150.h"

namespace rrfw {
    class RrOpGyroScope : public RrOpBase {
    public:
        RrOpGyroScope(BoschSensorClass imu):
        _imu{imu} {}
        
        ~RrOpGyroScope();
        const RrOpStorage execute(const RrOpStorage  bytes) override;

    private:
        BoschSensorClass _imu;
    };
}

#endif
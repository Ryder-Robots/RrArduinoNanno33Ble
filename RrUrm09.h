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
#include "RrOpBase.h"
#include "RrIsr.h"

namespace rrfw {
    class RrUrm09 : public RrOpBase {
        public:

            // Uses reasonable defaults, so no need to set it in config class, except for address.
            RrUrm09(uint8_t addr, uint8_t cmd, Isr &isr, uint8_t measureMode = MEASURE_MODE_AUTOMATIC, uint8_t measureRange = MEASURE_RANG_500);
            
            ~RrUrm09() {}

            const RrOpStorage execute(const RrOpStorage  bytes) override;

            int available() override;

        private:
            // Keep each instance containerised, to avoid conflicts.
            DFRobot_URM09 _urm = DFRobot_URM09();
            uint8_t _addr;
            uint8_t _measureMode;
            uint8_t _measureRange;
            float* _res;
            Isr    _isr;
    };
}

#endif 
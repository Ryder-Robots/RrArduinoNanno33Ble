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

#include "RrUrm09.h"

namespace rrfw
{
    RrUrm09::RrUrm09(uint8_t addr, uint8_t measureMode, uint8_t measureRange) : _addr{addr},
                                                                                _measureMode{measureMode},
                                                                                _measureRange{measureRange},
                                                                                _res{reinterpret_cast<float *>(calloc(2, sizeof(float)))}
    {
        while (!_urm.begin(_addr))
        {
            // TODO: Return some sort of response here.
            Serial.println("I2c device number error");
        }

        _urm.setModeRange(_measureMode, _measureRange);
    }

    /*!
     * request information from sensor, then store it in the data array.
     */
    const RrOpStorage RrUrm09::execute(const RrOpStorage bytes)
    {
        _res[0] = static_cast<float>(_urm.getDistance());
        _res[1] = _urm.getTemperature();
        size_t sz = (2 * sizeof(float));
        return RrOpStorage(RR_IO_RES_OK, sz, reinterpret_cast<uint8_t *>(_res));
    }

}
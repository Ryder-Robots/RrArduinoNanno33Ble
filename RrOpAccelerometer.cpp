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

#include "RrOpAccelerometer.h"

namespace rrfw {
        const RrOpStorage RrOpAccelerometer::execute(const RrOpStorage  bytes) {
            bytes._data;
            float *res = reinterpret_cast<float *>(calloc(4, sizeof(float)));
            res[0] = _imu.accelerationSampleRate();
            if (_imu.accelerationAvailable()) {
                _imu.readAcceleration(res[1], res[2], res[3]);
            } else {
                // TODO: return failed message.
                Serial.println("failed to read gyroscope");
            }

            uint8_t *data = reinterpret_cast<uint8_t *>(res);
            size_t sz = (4 * sizeof(float));

            return RrOpStorage(RR_IO_RES_OK, sz, data);
        }
}
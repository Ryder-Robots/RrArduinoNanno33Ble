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
 * Base class fior actions that can be performed by chip.
 */

#ifndef TXRX_BASE_HPP
#define TXRX_BASE_HPP

#include <stdint.h>

#include "RrCmd.h"
#include "RrOpStorage.h"

namespace rrfw {

class RrOpBase {
   public:
    /*!
     * @fn execute
     * @brief performs execute on the sensor, should be performed once available returns true.
     * @return Storage class that contains data defined in sesnsors driver, otherwise RR_IO_RES_UNSUPORTED
     */
    virtual const RrOpStorage execute(const RrOpStorage bytes) {
        uint8_t data[]{};
        return RrOpStorage(RR_IO_RES_UNSUPPORTED, 0, data);
    }

    /*!
     * @fn avialable
     * @brief returns true when sensor becomes available.
     * @return sensor implementation specific,  but usually bytes available.
     */
    virtual int available() { return 0; }

    virtual ~RrOpBase() {}
};
}  // namespace rrfw

#endif // TXRX_BASE_HPP
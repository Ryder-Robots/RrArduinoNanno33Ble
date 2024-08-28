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
 * This class is expected to run in the ISR call of the chip, It's constructor 
 * will have a list of supported commands given to it and the class will 
 * be called each time there is data avialable on the bus it is listening to.
 */

#ifndef RRISR_H
#define RRISR_H

#include <cstdlib>
#include <string.h>
#include "RrOpStorage.h"
#include "RrCmd.h"
#include "RrIsr.h"

namespace rrfw {
    class Isr {
    public:

        // deserilize bytes from an incomming request. And return the containerized image.
        const RrOpStorage deserialize(const uint8_t*, size_t);

    };
}

#endif
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
#include <stdint.h>
#include <Arduino.h>
#include "RrOpStorage.h"
#include "RrCmd.h"
#include "RrIsr.h"

namespace rrfw {
    #define SERIAL_BUS SerialUSB
    class Isr {
    public:

        /*!
         * @fn Isr
         * @brief class constructor
         */
        Isr() {}

        void begin(unsigned long boardRate);

        // deserilize bytes from an incomming request. And return the containerized image.
        /*!
         * @fn deseralize()
         * @brief deserialize raw input from serial port, and return the deserialized object.
         * @return Storage object
         */
        const RrOpStorage deserialize(const uint8_t*, size_t);

        /*!
         * @fn serialize
         * @brief convert storage object to uint8_t array
         * @return storage object.
         */
        const uint8_t* serialize(const RrOpStorage);

        /*!
         * @fn transmit
         * @brief sends result to Serial bus that communicates with the Pi, Note that the serial object will
         * have '\n' char appended to it, to inidcate a entire object.
         */
        void transmit(const RrOpStorage);

        /*!
         * @fn recieve()
         * @brief recieves an inbound request. This function should only be called as part of the interrupt in INO sketch,
         * and not directly.
         */
        const RrOpStorage recieve();
    };
}

#endif
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
 * Config,  this can be specific to a micro-processor,  and shoudl support only 
 * operations which are allowed.
 * 
 * Note that outside of this header,  and the associated implementation, all calling
 * functions should be unaware of the concrete implementation of the drivers.
 * 
 * They should also have no knowledge of pin layout, and setup. With the exception
 * of items that need to generate data on a timer such as GPS.
 */

#ifndef RRCONFIG_H
#define RRCONFIG_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "Arduino_BMI270_BMM150.h"
#include "RrIsr.h"
#include "OperationElementContainer.h"
#include "RrOpGyroScope.h"
#include "RrOpAccelerometer.h"
#include "RrMagnetoMeter.h"
#include "RrUrm09.h"

namespace rrfw {
    class RrConfig {
        public:
            /*!
             * class constructor
             */
            RrConfig() {}

            /*!
             * @fn ~RrConfig
             * @brief deconstructor.
             */
            ~RrConfig();

            /*!
             * @fn begin
             * @brief perform any initlization that is required.
             * @param ISR object.
             */
            void begin(Isr &isr);
        
            /*!
             * @fn get_supported_ops()
             * @brief lists all supported operations.
             * @return supported operations
             */
            OpElCnt*  get_supported_ops();

            /*!
             * @fn get_supported_ope_count()
             * @brief returns count of supported operations
             * @return supported operations count.
             */
            uint8_t   get_supported_ops_count();

            // This method can be called at startup,  
            // periodically have its data updated, like a GPS.
            //
            // A static_cast must be applied to the return operational reference,
            // so that it references correct functionality.
            /*!
             * @fn get_op
             * @brief given a CMD (op command) return the operation class wrapper.
             * @return operation object.
             */
            OpElCnt*  get_op(const RR_CMD cmd);

        // Extend onto private routine any specific configuration items,
        // such as PINs etc.
         private:
            OpElCnt*   _supported_ops;
            uint8_t   _supported_op_count;
    };
}

#endif
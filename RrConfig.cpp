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


#include "RrConfig.h"

// namespace rrfw {

//     /*
//      * Reserve space for the storage objects, and create 
//      */
//     RrConfig::RrConfig() {

//         // Add together all the objects,  their sizes can vary so we get the 
//         // size as a total.
//         size_t sz = sizeof(RrOpBase) + sizeof(OpElCnt);
        
//         // This must reflect the count of all object in the array.
//         _supported_op_count = 1;


//         _supported_ops = (RrOpStorage *) calloc(1, sz);

//         // Create and add the objects
//         _supported_ops[0] = new OpElCnt(RR_CMD_U1, new RrOpBase());
//     }

//     /*
//      * Release the memory
//      */
//     RrConfig::~RrConfig() {
//         for (int i = 0; i < _supported_op_count; i++) {
//             delete(_supported_ops[i]);
//         }
//     }

//     /***************************************
//      * Return the supported operations.
//      */
//     OpElCnt* RrConfig::get_supported_ops() {
//         return _supported_ops;
//     }

//     uint8_t RrConfig::get_supported_ops_count() {
//         return _supported_op_count;
//     }

//     /*!
//      * Return supportred op based on command.
//      */
//     /*
//      * just use a bubble search here, while bsearch is more efficient, the sorting algorithm
//      * will make it the same time, and avoid errors by not trying to sort it ourselves.
//      */
//     OpElCnt* RrConfig::get_op(RR_CMD cmd) {
//         OpElCnt* el;
//         bool found = false;
//         for (int i = 0; i < _supported_op_count) {
//             if (_supported_ops[i]->_cmd == cmd) {
//                 found = true;
//                 el = _supported_ops_count[i];
//                 break;
//             }
//         }

//         if (!found) {
//             el = (RrOpStorage *) calloc(1, sizeof(RrOpBase) + sizeof(OpElCnt));
//             el = new OpElCnt(RR_CMD_U1, new RrOpBase()); 
//         }

//         return el;
//     }
// }


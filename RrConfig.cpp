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
 * Config,  this can be specific to a micro-processor,  and should support only
 * operations which are allowed.
 *
 * Note that outside of this header,  and the associated implementation, all calling
 * functions should be unaware of the concrete implementation of the drivers.
 *
 * They should also have no knowledge of pin layout, and setup. With the exception
 * of items that need to generate data on a timer such as GPS.
 */

#include "RrConfig.h"
#include "Arduino_BMI270_BMM150.h"

namespace rrfw
{

    /*
     * Reserve space for the storage objects, and create
     */
    void RrConfig::begin(Isr &isr)
    {
        // Add together all the objects,  their sizes can vary so we get the
        // size as a total.
        const size_t sz = sizeof(OpElCnt);
        int support_cnt = 0;
        _supported_op_count = RR_LAST_CMD - RR_FIRST_CMD + 1;

        // This must reflect the count of all object in the array.
        _supported_ops = reinterpret_cast<OpElCnt *>(calloc(_supported_op_count, sz));

        // Create and add the objects
        _supported_ops[support_cnt++] = OpElCnt(RR_CMD_U1, new RrOpBase());
        _supported_ops[support_cnt++] = OpElCnt(RR_CMD_U2, new RrOpBase());

        // I2C devices
        _supported_ops[support_cnt++] = OpElCnt(RR_CMD_U8, new RrUrm09(RR_U8, RR_CMD_U8));
        _supported_ops[support_cnt++] = OpElCnt(RR_CMD_U9, new RrUrm09(RR_U9, RR_CMD_U8));

        if (!IMU.begin())
        {
            // Use C5 to indicate something is wrong with the IMU, we won't know exactly what is broken
            // but it is internal to the chip.
            float *_res = reinterpret_cast<float *>(calloc(2, sizeof(float)));
            _res[0] = static_cast<float>(RR_CMD_U5);
            _res[1] = 0;
            size_t rsz = (2 * sizeof(float));
            const RrOpStorage res = RrOpStorage(RR_IO_RES_FAILED, rsz, reinterpret_cast<uint8_t *>(_res));
            isr.transmit(res);
            _res = NULL;
        }

        RrOpBase *op = new RrOpGyroScope(IMU);
        _supported_ops[support_cnt++] = OpElCnt(RR_CMD_U5, op);

        RrOpBase *mm = new RrMagnetoMeter(IMU);
        _supported_ops[support_cnt++] = OpElCnt(RR_CMD_U7, mm);

        RrOpBase *ac = new RrOpAccelerometer(IMU);
        _supported_ops[support_cnt] = OpElCnt(RR_CMD_U6, ac);

        // send message back to Pi to let it know that IMU is now online.
        float *_res = reinterpret_cast<float *>(calloc(2, sizeof(float)));
        _res[0] = static_cast<float>(RR_CMD_U5);
        _res[1] = 0;
        size_t rsz = (2 * sizeof(float));
        const RrOpStorage res = RrOpStorage(RR_IO_RES_READY, sz, reinterpret_cast<uint8_t *>(_res));
        isr.transmit(res);
        _res = NULL;
    }

    /*
     * Release the memory
     */
    RrConfig::~RrConfig()
    {
    }

    /***************************************
     * Return the supported operations.
     */
    OpElCnt *RrConfig::get_supported_ops()
    {
        return _supported_ops;
    }

    uint8_t RrConfig::get_supported_ops_count()
    {
        return _supported_op_count;
    }

    /*!
     * Return supportred op based on command.
     */
    /*
     * just use a bubble search here, while bsearch is more efficient, the sorting algorithm
     * will make it the same time, and avoid errors by not trying to sort it ourselves.
     */
    OpElCnt *RrConfig::get_op(const RR_CMD cmd)
    {
        OpElCnt *el;
        bool found = false;
        for (int i = 0; i < _supported_op_count; i++)
        {
            if (_supported_ops[i]._cmd_id == cmd)
            {
                found = true;
                el = &_supported_ops[i];
                break;
            }
        }

        if (!found)
        {
            el = new OpElCnt(RR_CMD_U1, new RrOpBase());
        }

        return el;
    }
}

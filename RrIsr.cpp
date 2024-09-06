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

#include "RrIsr.h"

namespace rrfw
{
    void Isr::begin(unsigned long boardRate)
    {
        SERIAL_BUS.begin(boardRate);
        while (!Serial)
            ;
    }

    // Life becomes a lot easier once our data is deserialized,  because we can
    // operate on the object rather than the raw data, or in the case of I2C the
    // data slightly deserialized and returned by SMB.
    /*!
     * serialize byte array in I2C (SMB) format to a storage object for internal use.
     */
    const RrOpStorage Isr::deserialize(const uint8_t *ingres, size_t sz)
    {

        RR_CMD default_cmd = RR_IO_RES_BAD_RQ;
        uint8_t default_sz = 2;
        // verify that the size matches the contents getting sent.
        if (sz < 2 || sizeof(ingres) < 2)
        {
            // throw an error at this point.
            return RrOpStorage(default_cmd, default_sz, {});
        }
        default_sz = ingres[1];
        for (uint8_t c = RR_FIRST_CMD; c != RR_LAST_CMD; c++)
        {
            if (c == ingres[0])
            {
                default_cmd = static_cast<RR_CMD>(c);
                break;
            }
        }

        if (default_cmd == RR_IO_RES_BAD_RQ)
        {
            return RrOpStorage(default_cmd, 0, {});
        }

        uint8_t *data = reinterpret_cast<uint8_t *>(calloc(default_sz, sizeof(uint8_t)));
        memcpy(data, &ingres[2], default_sz + 1);
        RrOpStorage ret = RrOpStorage(default_cmd, default_sz, data);
        return ret;
    }

    /*!
     * Serialize storage value to byte array in I2C (SMB) format.
     *
     * @param req item to be serialized.
     * @return serialized result
     */
    const uint8_t *Isr::serialize(const RrOpStorage req)
    {
        uint8_t *data = reinterpret_cast<uint8_t *>(calloc(req._sz + 2, sizeof(uint8_t)));
        data[0] = static_cast<uint8_t>(req._cmd);
        data[1] = req._sz;

        if (req._sz > 0)
        {
            memcpy(&data[2], req._data, req._sz);
        }

        return data;
    }

    void Isr::transmit(const RrOpStorage tx)
    {
        const uint8_t *data = serialize(tx);
        size_t sz = tx._sz + 2;

        SERIAL_BUS.write(data, sz);
        SERIAL_BUS.println();
        SERIAL_BUS.flush();
    }

    const size_t Isr::recieve(RrOpStorage &rx)
    {
        uint8_t *data = NULL;
        size_t sz = 0;
        bzero(_buf, BUFSZ);
        if (SERIAL_BUS.available())
        {
            sz = SERIAL_BUS.readBytesUntil('\n', _buf, BUFSZ);
        }

        // It's a bad request either too much data, or timeout.
        // In both cases assume not ready
        if (sz > MAX_SZ || sz < 2)
        {
            uint8_t data[]{};
            rx = rrfw::RrOpStorage(RR_IO_RES_NOTREADY, 0, data);
            return 0;
        }

        data = reinterpret_cast<uint8_t *>(calloc(sz, sizeof(uint8_t)));
        memcpy(data, _buf, sz + 1);
        rx = deserialize(data, sz);

        // Free up the memory
        free(data);
        return sz;
    }
}
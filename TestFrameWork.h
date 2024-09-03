#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <Arduino.h>
#include <string.h>

namespace rrfwtest {
    void assertEquals(u_int8_t exp, int act, u_int8_t msg)
    {
        Serial.print(msg + " :");
        assert(exp == act);
        Serial.println("ok");
    }

    void assertEquals(int exp, int act, String msg)
    {
        Serial.print(msg + " :");
        assert(exp == act);
        Serial.println("ok");
    }

    void assertEquals_uint8(uint8_t exp, uint8_t act, String msg)
    {
        Serial.print(msg + " :");
        assert(exp == act);
        Serial.println("ok");
    }
}

#endif
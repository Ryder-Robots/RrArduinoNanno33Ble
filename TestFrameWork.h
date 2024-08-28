#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <Arduino.h>
#include <string.h>

namespace rrfwtest {
    void assertEquals(int exp, int act, String msg)
    {
        Serial.print(msg + " :");
        assert(exp == act);
        Serial.println("ok");
    }

    void assertEquals(uint8_t *exp, uint8_t *act, String msg)
    {
        String s1 = (char *) exp;
        String s2 = (char *) act;
        Serial.print(msg + " :");
        assert(s1.compareTo(s2) == 0);
        Serial.println("ok");
    }
}

#endif
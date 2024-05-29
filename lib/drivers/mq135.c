#ifndef NATIVE_TESTING
// Mocking file for mq135.h until we have the actual sensor driver coded (if we do it)

#include "mq135.h"

// Code to read the MQ135 sensor value
float mq135_read()
{
    float sensorValue = 0.3; // Placeholder value, replace with actual sensor reading

    return sensorValue;
}
#endif
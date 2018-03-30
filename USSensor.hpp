/**************************************************************
 * File: USSensor.hpp
 *
 * Description: Provides the class definition for an ultra-
 *              sonic sensor. Provides utilities for triggering
 *              the sending and receiving of the sound waves. 
 *
 * Author: Group 1
 **************************************************************/

/* Header Guard */
#ifndef USSENSOR_H
#define USSENSOR_H

/* Standard library includes */
#include <Arduino.h>

class USSensor {
    public:
        /**
         * Constructor.
         * 
         * @param triggerPin Pin number that controls the trigger of the sound waves
         * @param echoPin Pin number that listens for the echo of the sound waves
         */
        USSensor(uint8_t triggerPin, uint8_t echoPin);

        /**
         * Reads the current distance from any barriers. Uses the timeout value
         * provided to limit the call length. The call will block until a value
         * is determined or the call times out. If there is a timeout the return
         * value will be set to -1.
         * 
         * @param timeout Max time to wait in microseconds
         * @return int8_t Distance in centimeters to any barrier
         */
        int8_t readDistance(uint8_t timeout);

        /**
         * Returns true if the last distance read was different than
         * the one before it.
         * 
         * @return boolean True if the distance has changed, False otherwise
         */
        boolean isNewDistance();

    private:
        /* Variables to hold the pins */
        uint8_t triggerPin;
        uint8_t echoPin;

        /* Hold the most recent data to check for changes */
        int8_t lastDistance;
        int8_t currentDistance;
};

#endif
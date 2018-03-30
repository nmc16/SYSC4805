/**************************************************************
 * File: USSensorListener.hpp
 *
 * Description: Listener interface for ultrasonic sensors.
 *
 * Author: Group 1
 **************************************************************/

/* Header Guard */
#ifndef USSENSORLISTENER_H
#define USSENSORLISTENER_H

/* Standard library includes */
#include <stdint.h>

class USSensorListener {
    
    public:
        /**
         * Destructor.
         */
	    virtual ~USSensorListener() {}

        /**
         * Updates motor controller using the sensor data that was read.
         * 
         * Assumes that the distances array orders the data by the
         * clockwise arrangement of the sensors.
         * 
         * @param distances Array of distances from the sensors
         * @param distances_size Size of the distances array
         */
        virtual void update(int8_t distances[], size_t distances_size) = 0;
};

#endif

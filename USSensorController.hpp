/**************************************************************
 * File: USSensorController.hpp
 *
 * Description: Handles all of the ultrasonic sensors.
 *              Reads the distances from all the sensors
 *              and provides updates to listeners.
 *
 * Author: Group 1
 **************************************************************/

/* Header Guard */
#ifndef USSENSORCONTROLLER_H
#define USSENSORCONTROLLER_H

/* Package includes */
#include "USSensor.hpp"
#include "Collection.h"

class USSensorListener {

};

class USSensorController {
    public:
        
        /**
         * Constructor.
         */
        USSensorController();

        /**
         * Adds an ultrasonic sensor to the list of controlled sensors.
         * 
         * @param sensor Ultrasonic sensor to add
         */
        void addSensor(USSensor* sensor);

        /**
         * Adds a listener for the ultrasonic sensors. The listener's
         * callback function will be called if one of the sensors reads
         * a value outside of the normal threshold (i.e. a wall appears 
         * or disappears)
         * 
         * @param listener Listener to add
         */
        void addListener(USSensorListener* listener);

        /**
         * Reads all of the tracked ultrasonic sensors. Updates all
         * listeners if there is any changed data from the sensors.
         */
        void readSensors();

    private:
        /* Collections for the listeners and sensors */
        Collection<USSensor*> sensors;
        Collection<USSensorListener*> listeners;      
};

#endif
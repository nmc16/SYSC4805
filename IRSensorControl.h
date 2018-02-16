/**************************************************************
 * File: IRSensorControl.h
 *
 * Description: Reads the data from the IR sensors on the
 *              robot. Holds collection of registered listeners
 *              that can be updated with new data.
 * 
 * Notes: IR sensor reading requires the user to manually read
 *        the sensors. Library does not contain any threads
 *        because of memory constraints.
 *
 * Public Functions: void addListener(IRListener&)
 *                   void readSensors()
 * 
 * @author Group 1
 **************************************************************/

#ifndef IRSensorControl_h
#define IRSensorControl_h

/* Includes */
#include <Arduino.h>
#include <stdint.h>
#include "Collection.h"

/* Class Definitions */
class IRListener {
	public:
	    virtual ~IRListener() {}
        virtual void update(uint8_t rightData, uint8_t leftData) = 0;
};

class IRSensorControl {
    public:
		/**
		 * Constructor.
		 * 
		 * @param rightSensor pin of the right sensor input
		 * @param leftSensor pin of the left sensor input
		 */
	    IRSensorControl(uint8_t rightSensor, uint8_t leftSensor);

		/**
		 * Add a listener to the collection to be updated when a new
		 * value is read from one of the sensors.
		 * 
		 * @param listener IRListener to update when new data is read
		 */
		void addListener(IRListener* listener);

		/**
		 * Reads the current data from the sensors. If the data is
		 * different that the previous cached value, the listeners
		 * will all be updated.
		 */
		void readSensors();

		char* toString(char* buffer, size_t bufferSize);
	
	private:
	    /* Pins for the sensors */
        uint8_t rightSensor;
		uint8_t leftSensor;

	    /* Cached data */
        uint8_t rightData;
		uint8_t leftData;

		/* Collection of listeners */
		Collection<IRListener*> listeners;

	    /**
		 * Updates all registered listeners with the current cached data.
		 */
	    void updateListeners();
};

#endif // define


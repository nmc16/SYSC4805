/**************************************************************
 * File: IRSensorControl.c
 *
 * Description: Reads the data from the IR sensors on the
 *              robot. Holds collection of registered listeners
 *              that can be updated with new data.
 * 
 * @author Group 1
 **************************************************************/

/* Standard Library Includes */
#include <stdio.h>

/* Other Includes */
#include "IRSensorControl.h"

/* Defines */
bool updated = false;

IRSensorControl::IRSensorControl(uint8_t rightSensor, uint8_t leftSensor) {
    /* Store the sensor pins and reset the sensor data */
    this->rightSensor = rightSensor;
    this->leftSensor = leftSensor;

    this->rightData = 0;
    this->leftData = 0;

    /* Ensure that the pins to input mode */
	pinMode(this->rightSensor, INPUT);
	pinMode(this->leftSensor, INPUT);
}

void IRSensorControl::addListener(IRListener* listener) {
    this->listeners.push(listener);
}

void IRSensorControl::readSensors() {
    /* Read the new values from the sensors */
    uint8_t newRightData = digitalRead(this->rightSensor);
    uint8_t newLeftData = digitalRead(this->leftSensor);

    /*
     * Compare to our cached value, if they are the same
     * we can just skip updating the listeners entirely
     */
    if (newRightData == this->rightData && newLeftData == this->leftData) {
        updated = false;
        return;
    }

    updated = true;
    /* Otherwise update the cache and call the listeners */
    this->rightData = newRightData;
    this->leftData = newLeftData;
    this->updateListeners();
}

void IRSensorControl::updateListeners() {
    for (int i = 0; i < this->listeners.size(); i++) {
        listeners[i]->update(this->rightData, this->leftData);
    }
}

char* IRSensorControl::toString(char* buffer, size_t bufferSize) {
    snprintf(buffer, 
	         bufferSize, 
			 "IRSensorControl[Right Sensor=%d, Left Sensor=%d, Updated=%d]", 
			 this->rightData, this->leftData, updated);

	return buffer;
}

/**************************************************************
 * File: USSensorController.cpp
 *
 * Description: Handles all of the ultrasonic sensors.
 *              Reads the distances from all the sensors
 *              and provides updates to listeners.
 *
 * Author: Group 1
 **************************************************************/

/* Package Includes */
#include "USSensorController.hpp"

USSensorController::USSensorController() {
    /* Empty constructor */
}

void USSensorController::addSensor(USSensor* sensor) {
    this->sensors.push(sensor);
}

void USSensorController::addListener(USSensorListener* listener) {
    this->listeners.push(listener);
}

void USSensorController::readSensors() {
    size_t i;
    int8_t distances[this->sensors.size()];
    boolean requiresUpdate = false;
    Serial.begin(115200);

    /* Read all the distance values from the sensors */
    for (i = 0; i < this->sensors.size(); i++) {
        distances[i] = this->sensors[i]->readDistance(0);
        Serial.println(distances[i]);
        requiresUpdate |= this->sensors[i]->isNewDistance();
    }

    /* If there was no change we can just leave the method */
    if (!requiresUpdate) {
        Serial.println("Not updating listeners");
        return;
    }

    /* Otherwise we need to update all the listeners */
    Serial.println("Updating listeners");
    for (i = 0; this->listeners.size(); i++) {
        this->listeners[i]->update(distances, this->sensors.size());
    }
}

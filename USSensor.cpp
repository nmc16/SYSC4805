/**************************************************************
 * File: USSensor.cpp
 *
 * Description: Controls the ultrasonic sensor on the
 *              designated pins.
 *
 * Author: Group 1
 **************************************************************/

/* Package Includes */
#include "USSensor.hpp"

USSensor::USSensor(uint8_t triggerPin, uint8_t echoPin) {
    /* Store the pins */
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;

    /* Set the pins to the correct input/output state */
    pinMode(this->triggerPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

uint8_t USSensor::readDistance(uint8_t timeout) {
    uint16_t duration;
    
    /* Send the pulse for 10 microseconds */
    digitalWrite(this->triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->triggerPin, LOW);

    /* Try and read the reflected pulse */
    if ((duration = (uint16_t) pulseIn(this->echoPin, HIGH, timeout)) == 0) {
        return -1;
    }

    /* Calculate the distance in cm */
    return (int8_t) (duration * 0.0171);
}
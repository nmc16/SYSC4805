/**************************************************************
 * File: IRSensorMotorListener.h
 *
 * Description: 
 *
 * Public Functions: 
 * 
 * @author Group 1
 **************************************************************/

#include "IRSensorMotorListener.h"

Direction direction = Direction::BACKWARD;
uint8_t speed = 255;

IRSensorMotorListener::IRSensorMotorListener(MovementControl *controller) {
    this->movementControl = controller;
}

void IRSensorMotorListener::update(uint8_t rightData, uint8_t leftData) {
    if (!rightData && !leftData) {
        this->movementControl->setDirection(Direction::FORWARD);
        this->movementControl->setSpeed(5);
        direction = Direction::FORWARD;
        speed = 5;
    } else if (leftData) {
        this->movementControl->setDirection(Direction::LEFT);
        this->movementControl->setSpeed(5);
        direction = Direction::LEFT;
        speed = 5;
    } else if (rightData) {
        this->movementControl->setDirection(Direction::RIGHT);
        this->movementControl->setSpeed(5);
        direction = Direction::RIGHT;
        speed = 5;
    } else {
        this->movementControl->setDirection(Direction::BACKWARD);
        this->movementControl->setSpeed(0);
        direction = Direction::BACKWARD;
        speed = 5;
    }
}

char* IRSensorMotorListener::toString(char* buffer, size_t bufferSize) {
    snprintf(buffer, 
	         bufferSize, 
			 "IRSensorMotorListener[Direction=%d, Speed=%d, Controller=%p]", 
			 direction, speed, this->movementControl);

	return buffer;
}
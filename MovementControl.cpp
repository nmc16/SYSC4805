/**************************************************************
 * File: MovementControl.cpp
 *
 * Description: Controls the speed and direction of the robot
 *              through the 4 pins.
 *
 * @author Group 1
 **************************************************************/

/* Standard Library Includes */
#include <stdio.h>

/* Other Includes */
#include "MovementControl.hpp"

/* Defines */
#define TO_STRING_BUFFER_SIZE 256
#define SPEED_MULTIPLIER 25
#define SPEED_LEVEL_STOPPED 0
#define SPEED_LEVEL_MAX 10
#define MOTOR_DIRECTION_FORWARD 1
#define MOTOR_DIRECTION_BACKWARD 0
#define MOTOR_SPEED(level, direction, scale) {\
	(uint8_t) ((direction) ? (10 - level) * SPEED_MULTIPLIER * scale : (level) * SPEED_MULTIPLIER * scale)}

MovementControl::MovementControl(uint8_t A_IA, uint8_t A_IB, uint8_t B_IA, uint8_t B_IB) {
	/* Store the pins that were passed in */
	this->pinASpeed = A_IA;
	this->pinADirection = A_IB;
	this->pinBSpeed = B_IA;
	this->pinBDirection = B_IB;

	/* Ensure that the pins to output mode */
	pinMode(this->pinASpeed, OUTPUT);
	pinMode(this->pinADirection, OUTPUT);
	pinMode(this->pinBSpeed, OUTPUT);
	pinMode(this->pinBDirection, OUTPUT);

	/* Initialize the motor so that we are not moving but store a forward direction */
	this->currentSpeedLevel = SPEED_LEVEL_STOPPED;
	this->currentDirection = Direction::FORWARD;

    /* Initially ignore the scaling factors, let user set them later */
    this->motorLeftScale = 1;
	this->motorRightScale = 1;

	/* Send the initial data to the motor pins */
	updateMotor();
}

void MovementControl::setDirection(Direction direction) {
	/* Update the direction */
	this->currentDirection = direction;

	/* Need to update the motor pins with the new direction */
	updateMotor();
}

void MovementControl::setSpeed(uint8_t speed) {
	/* We take the speed as a level so make sure it is within our bounds */
	if (speed < SPEED_LEVEL_STOPPED) {
		speed = SPEED_LEVEL_STOPPED;
	}

	if (speed > SPEED_LEVEL_MAX) {
		speed = SPEED_LEVEL_MAX;
	}

	/* Store the current speed for the motor */
	this->currentSpeedLevel = speed;
	updateMotor();
}

void MovementControl::setLeftScale(float factor) {
	this->motorLeftScale = factor;
}

void MovementControl::setRightScale(float factor) {
	this->motorRightScale = factor;
}

void MovementControl::updateMotor() {
	/* Change the direction based on the current direction */
	switch (this->currentDirection) {
		case Direction::FORWARD:
		{
			/* Update the direction of the motors */
			this->motorLeftDirection = MOTOR_DIRECTION_FORWARD;
			this->motorRightDirection = MOTOR_DIRECTION_FORWARD;

			/* Calculate the new speeds */
			this->motorLeftSpeed = MOTOR_SPEED(this->currentSpeedLevel, MOTOR_DIRECTION_FORWARD, this->motorLeftScale);
			this->motorRightSpeed = MOTOR_SPEED(this->currentSpeedLevel, MOTOR_DIRECTION_FORWARD, this->motorRightScale);
			break;
		}
		case Direction::RIGHT:
		{
			/* We only need to stop the right motor so that the left motor
			 * will continue in either direction */
			this->motorRightSpeed = MOTOR_SPEED(0, this->motorRightDirection, this->motorRightScale);
			this->motorLeftSpeed = MOTOR_SPEED(this->currentSpeedLevel, this->motorLeftDirection, this->motorLeftScale);
			break;
		}
		case Direction::LEFT:
		{
			/* We only need to stop the left motor so that the right will
			 * continue in either direction */
			this->motorRightSpeed = MOTOR_SPEED(this->currentSpeedLevel, this->motorRightDirection, this->motorRightScale);
			this->motorLeftSpeed = MOTOR_SPEED(0, this->motorLeftDirection, this->motorLeftScale);
			break;
		}
		case Direction::BACKWARD:
		{
			/* Update the direction of the motors */
			this->motorLeftDirection = MOTOR_DIRECTION_BACKWARD;
			this->motorRightDirection = MOTOR_DIRECTION_BACKWARD;

			/* Update the speeds of the motors */
			this->motorLeftSpeed = MOTOR_SPEED(this->currentSpeedLevel, MOTOR_DIRECTION_BACKWARD, this->motorLeftScale);
			this->motorRightSpeed = MOTOR_SPEED(this->currentSpeedLevel, MOTOR_DIRECTION_BACKWARD, this->motorRightScale);
		}
	}

	/* Write our new values to the control pins */
	digitalWrite(this->pinBDirection, this->motorLeftDirection);
	digitalWrite(this->pinADirection, this->motorRightDirection);
	analogWrite(this->pinBSpeed, this->motorLeftSpeed);
	analogWrite(this->pinASpeed, this->motorRightSpeed);
}

char* MovementControl::toString(char* buffer, size_t buffer_size) {
	/*
	 * Allow the user to pass in the buffer if they want the string version.
	 * Point is to cut down on memory being used and forcing user to free
	 * memory created from this method.
	 */
	snprintf(buffer,
	         buffer_size,
			 "MovementControl[Speed Level=%d, Right Speed=%d, Left Speed=%d, Right Direction=%d, Left Direction=%d]",
			 this->currentSpeedLevel, this->motorRightSpeed, this->motorLeftSpeed,
			 this->motorRightDirection, this->motorLeftDirection);

	return buffer;
}

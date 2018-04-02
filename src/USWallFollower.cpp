/**************************************************************
 * File: USWallFollower.cpp
 *
 * Description: Ultrasonic sensor listener that implements the
 *              wall follower algorithm.
 *
 * Author: Group 1
 **************************************************************/

/* Package Includes */
#include "USWallFollower.hpp"

/* Defines */
#define MIN_DISTANCE 3 /* We don't want to get closer than 3 cm to the wall */
#define MAX_DISTANCE 7 /* If the wall is farther than 7 cm we need to get closer again */

/* Let's assume we have 3 sensors that go clockwise */
#define LEFT_SENSOR 0
#define FRONT_SENSOR 1
#define RIGHT_SENSOR 2

USWallFollower::USWallFollower(MovementControl* movementControl) {
    this->movementControl = movementControl;
}

void USWallFollower::update(int8_t distances[], size_t distances_size) {
	size_t i;

	/* Distances that time-out are given as -1, we need to convert those to the max values */
	for (i = 0; i < distances_size; i++) {
		if (distances[i] == -1) {
			distances[i] = INT8_MAX;
		}
	}

    /* Check if the left wall is present */
	if (distances[LEFT_SENSOR] > MAX_DISTANCE) {
		/* We lost the left wall so we need to initiate a turn left */
		this->movementControl->setDirection(Direction::LEFT);
	
	} else if (distances[LEFT_SENSOR] < MIN_DISTANCE) {
		/* We are too close to the left wall so we need to start turning right */
		this->movementControl->setDirection(Direction::RIGHT);
	
	} else if (distances[FRONT_SENSOR] > MAX_DISTANCE) {
		/* Otherwise if we can move forward keep moving forward */
		this->movementControl->setDirection(Direction::FORWARD);
	
	} else if (distances[RIGHT_SENSOR] > MAX_DISTANCE) {
		/* If there are walls on all sides except the right then we need to turn right */
		this->movementControl->setDirection(Direction::RIGHT);
	
	} else {
		/* Otherwise we have walls on all sides so we need to turn around */
		this->movementControl->turnAround();
	}
}

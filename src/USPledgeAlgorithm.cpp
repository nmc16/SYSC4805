/**************************************************************
* File: USPledgeAlgorithm.cpp
*
* Description: Ultrasonic sensor listener that implements the
*              pledge algorithm.
*
* Author: Group 1
**************************************************************/

/* Package Includes */
#include "USPledgeAlgorithm.hpp"

/* travel forward until we reach wall - consider this a node
   choose a random direction from that node and mark it
   continue until the end is reached or a dead end is reached 
   backtrack to last node and pick different direction 
   if node has no more directions then backtrack to last node 
   continue until exit is found */

/* Define the change in direction */
#define DIRECTION_CHANGE 15  /* Takes 6 iterations to move 90 degrees */

/* Defines */
#define MIN_DISTANCE 3 /* We don't want to get closer than 3 cm to the wall */
#define MAX_DISTANCE 7 /* If the wall is farther than 7 cm we need to get closer again */

/* Let's assume we have 3 sensors that go clockwise */
#define LEFT_SENSOR 0
#define FRONT_SENSOR 1
#define RIGHT_SENSOR 2

USPledgeAlgorithm::USPledgeAlgorithm(MovementControl* movementControl) {
	this->movementControl = movementControl;
	this->currentOrientation = 0;
}

uint8_t USPledgeAlgorithm::findClosestDirection() {
	if (this->currentOrientation < 45) {
		this->currentOrientation = 0;
	}
	else if (this->currentOrientation >= 45 && this->currentOrientation < 135) {
		this->currentOrientation = 90;
	} else if (this->currentOrientation >= 135 && this->currentOrientation < 225) {
		this->currentOrientation = 180;
	} else {
		this->currentOrientation = 270;
	}
}

void USPledgeAlgorithm::lhr(int8_t distances[], size_t distances_size) {

	/* Check if the left wall is present */
	if (distances[LEFT_SENSOR] > MAX_DISTANCE) {
		/* We lost the left wall so we need to initiate a turn left */
		this->movementControl->setDirection(Direction::LEFT);
		this->currentOrientation -= DIRECTION_CHANGE;

	} else if (distances[LEFT_SENSOR] < MIN_DISTANCE) {
		/* We are too close to the left wall so we need to start turning right */
		this->movementControl->setDirection(Direction::RIGHT);
		this->currentOrientation += DIRECTION_CHANGE;

	} else if (distances[FRONT_SENSOR] > MAX_DISTANCE) {
		/* Otherwise if we can move forward keep moving forward */
		this->movementControl->setDirection(Direction::FORWARD);

	}
	else if (distances[RIGHT_SENSOR] > MAX_DISTANCE) {
		/* If there are walls on all sides except the right then we need to turn right */
		this->movementControl->setDirection(Direction::RIGHT);
		this->currentOrientation += DIRECTION_CHANGE;

	} else {
		/* Otherwise we have walls on all sides so we need to turn around */
		this->movementControl->turnAround();
		this->currentOrientation += 180;
	}

	/* Ensure that the orientation is in the range of 0-360 */
	if (this->currentOrientation < 0) {
		this->currentOrientation = 360 - this->currentOrientation;
	}

	this->currentOrientation = this->currentOrientation % 360;
}

void USPledgeAlgorithm::update(int8_t distances[], size_t distances_size) {
	/* Steps for the Pledge Algorithm:
	 *     1) Always move towards the target orientation if possible 
	 *     2) If wall encountered then use left hand rule until orientation is available again 
	 *        (done by using sum of angles is 0) */
	size_t i;

	/* Distances that time-out are given as -1, we need to convert those to the max values */
	for (i = 0; i < distances_size; i++) {
		if (distances[i] == -1) {
			distances[i] = INT8_MAX;
		}
	}

	/* First check if we are going forward */
	if (this->movementControl->getDirection() == Direction::FORWARD) {
		/* We should round to reset errors that might arise */
		this->findClosestDirection();
	}

	/* Check if we are going the correct way */
	if (this->currentOrientation == 0) {
		/* Is there a wall in front of us blocking the way */
		if (distances[FRONT_SENSOR] < MAX_DISTANCE) {
			/* Then initiate the left-hand rule */
			this->lhr(distances, distances_size);
		
		} else {
			/* No wall so we can go forward */
			this->movementControl->setDirection(Direction::FORWARD);
		}

	} else {
		/* Otherwise we have to continue with the left-hand rule */
		this->lhr(distances, distances_size);
	}
}

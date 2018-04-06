/**************************************************************
 * File: USWallFollower.cpp
 *
 * Description: Ultrasonic sensor listener that implements the
 *              wall follower algorithm.
 *
 * Author: Group 1
 **************************************************************/

#include <Arduino.h>

/* Package Includes */
#include "USWallFollower.hpp"

/* Defines */
#define MIN_DISTANCE 4 /* We don't want to get closer than 3 cm to the wall */
#define MAX_DISTANCE 7 /* If the wall is farther than 7 cm we need to get closer again */

/* Let's assume we have 3 sensors that go clockwise */
#define LEFT_SENSOR 0
#define FRONT_SENSOR 1
#define RIGHT_SENSOR 2

int8_t old_di[3] = {0, 0, 0};
uint8_t pivoting = 0;
int8_t turnAroundRight = -1;
int8_t turnAroundLeft = -1;

USWallFollower::USWallFollower(MovementControl* movementControl) {
    this->movementControl = movementControl;
}

void USWallFollower::update(int8_t distances[], size_t distances_size) {
	size_t i;

    //memcpy(old_di, distances, sizeof(old_di));

	/* Distances that time-out are given as -1, we need to convert those to the max values */
	for (i = 0; i < distances_size; i++) {
		if (distances[i] == -1) {
			distances[i] = INT8_MAX;
		}
	}

    if (pivoting) {
        if ((distances[RIGHT_SENSOR] > turnAroundLeft - 3) && 
            (distances[LEFT_SENSOR] > turnAroundRight - 3) && (distances[LEFT_SENSOR] < turnAroundRight + 3) &&
            (distances[FRONT_SENSOR] > 20)) {
            pivoting = 0;
            this->movementControl->stopPivot();
        } else {
            this->movementControl->pivotRight();
        }
        return;
    }

    /* Check if the left wall is present */
	if (distances[LEFT_SENSOR] > MAX_DISTANCE && distances[LEFT_SENSOR] < 10) {
		/* We lost the left wall so we need to initiate a turn left */
		this->movementControl->setDirection(Direction::LEFT);
        
    } else if (distances[LEFT_SENSOR] > MAX_DISTANCE) {
        /* We lost the left wall so we need to initiate a turn left */
        this->movementControl->setDirection(Direction::FORWARD);
        delay(250);
        this->movementControl->setDirection(Direction::LEFT);
        delay(650);

    } else if (distances[LEFT_SENSOR] < MIN_DISTANCE && distances[FRONT_SENSOR] > 7) {
		/* We are too close to the left wall so we need to start turning right */
		this->movementControl->setDirection(Direction::RIGHT);
	
	} else if (distances[FRONT_SENSOR] > 7) {
		/* Otherwise if we can move forward keep moving forward */
		this->movementControl->setDirection(Direction::FORWARD);
	
	} else if (distances[RIGHT_SENSOR] > MAX_DISTANCE && distances[RIGHT_SENSOR] < 10) {
		/* If there are walls on all sides except the right then we need to turn right */
		this->movementControl->setDirection(Direction::RIGHT);
        //delay(1250);
    } else if (distances[RIGHT_SENSOR] > 13) {
        this->movementControl->setDirection(Direction::RIGHT);
        delay(1250);
	} else {
		/* Otherwise we have walls on all sides so we need to turn around */
        Serial.print("TURNING AROUND");
        Serial.println();
		//this->movementControl->turnAround();
        pivoting = 1;
        turnAroundLeft = distances[LEFT_SENSOR];
        turnAroundRight = distances[RIGHT_SENSOR];
	}
}

char* USWallFollower::toString(char* buffer, size_t buffer_size) {
    snprintf(buffer,
	         buffer_size,
			 "USWallFollower[]");
	return buffer;
}


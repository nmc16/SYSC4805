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
#define THRESHOLD_DISTANCE 4
#define FRONT_SENSOR 0
#define RIGHT_SENSOR 1

USWallFollower::USWallFollower(MovementControl* movementControl) {
    this->movementControl = movementControl;
}

void USWallFollower::update(int8_t distances[], size_t distances_size) {
    /* If there is an opening on the right side */
    if (distances[RIGHT_SENSOR] > THRESHOLD_DISTANCE || distances[RIGHT_SENSOR] == -1) {
        /* Then we want to turn right towards wall */
        this->movementControl->setDirection(Direction::RIGHT);
    
    } else if (distances[FRONT_SENSOR] > THRESHOLD_DISTANCE || distances[FRONT_SENSOR] == -1) {
        /* If there is no wall in front of the robot -> go forward */
        this->movementControl->setDirection(Direction::FORWARD);
    
    } else if (distances[FRONT_SENSOR] < THRESHOLD_DISTANCE && distances[FRONT_SENSOR] != -1) {
        /* There is a wall in front of us */
        if (distances[RIGHT_SENSOR] > THRESHOLD_DISTANCE || distances[RIGHT_SENSOR] == -1) {
            /* There is no wall on the right so turn right */
            this->movementControl->setDirection(Direction::RIGHT);
        
        } else {
            /* We have to turn around */
            this->movementControl->setDirection(Direction::RIGHT);
            delay(1000);
            this->movementControl->setDirection(Direction::FORWARD);
        }
    }
}

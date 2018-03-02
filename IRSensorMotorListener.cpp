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

#define WHITE 0
#define BLACK 1

Direction direction = Direction::BACKWARD;
uint8_t speed = 255;
uint8_t currentStep = 0;

uint8_t reset = 0;
uint8_t blackCount = 0;

IRSensorMotorListener::IRSensorMotorListener(MovementControl *controller) {
    this->movementControl = controller;
}

void IRSensorMotorListener::walkLine(uint8_t rightData, uint8_t leftData) {
    if (reset && rightData && !leftData) {
        reset = 0;
        this->movementControl->setDirection(Direction::FORWARD);
        direction = Direction::FORWARD;
    }

    if (reset) {
        return;
    }

    /* If both sensors are on white */
    if (rightData == WHITE && leftData == WHITE) {
        /* Then we need to turn towards the line */
        this->movementControl->setDirection(Direction::RIGHT);
        direction = Direction::RIGHT;
    
    } else if (rightData == BLACK && leftData == WHITE) {
        /*
         * If the right sensor is on black and the left is on white 
         * we want to start going straight again
         */

        this->movementControl->setDirection(Direction::FORWARD);
        direction = Direction::FORWARD;
    
    } else if (rightData == WHITE && leftData == BLACK) {
        /*
         * If the right sensor is on white and the left sensor
         * is on black we need to turn left
         */
        reset = 1;
        this->movementControl->setDirection(Direction::LEFT);
        direction = Direction::LEFT;
    }

    /* If they both are on black we don't know what to do */
}

void IRSensorMotorListener::moonWalk(uint8_t rightData, uint8_t leftData) {
    if (reset && rightData == WHITE && leftData == BLACK) {
        reset = 0;
        this->movementControl->setDirection(Direction::FORWARD);
        direction = Direction::FORWARD;
    }

    if (reset) {
        return;
    }

    /* If both sensors are on white */
    if (rightData == WHITE && leftData == WHITE) {
        /* Then we need to turn towards the line */
        this->movementControl->setDirection(Direction::LEFT);
        direction = Direction::LEFT;
    
    } else if (rightData == BLACK && leftData == WHITE) {
        /*
         * If the right sensor is on black and the left is on white 
         * we want to get back to the line
         */

        reset = 1;
        this->movementControl->setDirection(Direction::RIGHT);
        direction = Direction::RIGHT;
    
    } else if (rightData == WHITE && leftData == BLACK) {
        /*
         * If the right sensor is on white and the left sensor
         * is on black we can start going forward again
         */
        this->movementControl->setDirection(Direction::FORWARD);
        direction = Direction::FORWARD;
    }

    /* If they both are on black we don't know what to do */
}

void IRSensorMotorListener::update(uint8_t rightData, uint8_t leftData) {

    switch (currentStep) {
        /* Step zero goes along the first straight away */
        case 0: {
            /* 
             * If we hit two black lines we need to start to execute 
             * the left turn 
             */
            if (rightData && leftData) {
                /* Start executing the left turn */
                this->movementControl->setDirection(Direction::LEFT);
                direction = Direction::LEFT;
                currentStep++;
            } else {
                /* Otherwise we just walk the line like normal */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case 1: {
            /* 
             * Step 1: Execute turn to line 2
             * Goal is to wait for the right sensor to hit white during its turn 
             */
            if (!rightData) {
                currentStep++;
            }
            break;
        }
        case 2: {
            /* 
             * Step 2: Finish turn to line 2
             * Goal is to wait for the sensor to find the black line again
             */
            if (rightData && !leftData) {
                this->movementControl->setDirection(Direction::FORWARD);
                direction = Direction::FORWARD;
                currentStep++;
            }
            break;
        }
        case 3: {
            /* 
             * Step 3: Follow the line 2 until we hit T in road
             * Initiate right turn from line 2 to line 3
             */
            if (rightData == BLACK && leftData == BLACK) {
                this->movementControl->setDirection(Direction::RIGHT);
                direction = Direction::RIGHT;
                currentStep++;
            } else {
                /* Otherwise keep walking the line */
                this->walkLine(rightData, leftData);
            }
            break;
        }
        case 4: {
            /* 
             * Step 4: Keep turning until the left sensor hits
             *         the black line on line 3.
             * Goal: Stop the turn and begin walking line 3 to 4.
             */
            delay(1700);
            currentStep++;

            /* Otherwise we want it to keep turning */
            break;
        }
        case 5: {
            this->moonWalk(rightData, leftData);
            currentStep++;

            break;
        }
        case 6: {
            /* 
             * Step 6: Walk on line 4 until we hit junction of line 5.
             * Goal: Turn left on line 5.
             */
            if (rightData == BLACK && leftData == BLACK) {
                this->movementControl->setDirection(Direction::LEFT);
                direction = Direction::LEFT;
                currentStep++;
            } else {
                /* Otherwise walk the line */
                this->moonWalk(rightData, leftData);
            }
            break;
        }
        case 7: {
            /* 
             * Step 7: Turn until we've inverted the sensors so that
             *         right now follows the black line on line 6.
             * Goal: Stop the turn when right following line.
             */
            if (rightData == BLACK && leftData == WHITE) {
                this->moonWalk(rightData, leftData);
                currentStep++;
            }

            /* Otherwise keep turning */
            break;
        }
        case 8: {
            /* Turn right on line 6 */
            if (rightData == BLACK && leftData == BLACK) {
                this->movementControl->setDirection(Direction::RIGHT);
                direction = Direction::RIGHT;
                currentStep++;
            } else {
                this->moonWalk(rightData, leftData);
            }
            break;
        }
        case 9: {
            if (rightData == WHITE && leftData == BLACK) {
                this->moonWalk(rightData, leftData);
                currentStep++;
            }

            /* Otherwise keep turning */
            break;
        }
        case 10: {
            /* Turn right on line 7 */
            if (rightData == BLACK && leftData == BLACK) {
                this->movementControl->setDirection(Direction::RIGHT);
                direction = Direction::RIGHT;
                currentStep++;
            } else {
                this->moonWalk(rightData, leftData);
            }
            break;
        }
        case 11: {
            if (blackCount > 3) {
                currentStep++;
            }
            if (rightData == BLACK && leftData == BLACK) {
                blackCount++;
            } else {
                blackCount = 0;
            }
            this->moonWalk(rightData, leftData);
            break;
        }
        case 12: {
            this->movementControl->setSpeed(0);
            break;
        }
        default: {
            break;
        }
    }
}

char* IRSensorMotorListener::toString(char* buffer, size_t bufferSize) {
    snprintf(buffer, 
	         bufferSize, 
			 "IRSensorMotorListener[Direction=%d, Speed=%d, Step=%d, Controller=%p]", 
			 direction, speed, currentStep, this->movementControl);

	return buffer;
}

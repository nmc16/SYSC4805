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

/* Define methods to determine the color of the sensor */
#define ISBLACK(x) x
#define ISWHITE(x) !x

/* Define the step names */
#define WALK_LINE_ONE 0
#define TURN_ON_LINE_TWO 1
#define WALK_LINE_TWO 2
#define TURN_ON_LINE_THREE 3
#define WALK_LINE_THREE 4
#define TURN_ON_LINE_FOUR 5
#define WALK_LINE_FOUR 6
#define TURN_ON_LINE_FIVE 7
#define WALK_LINE_FIVE 8
#define TURN_ON_LINE_SIX 9
#define WALK_LINE_SIX 10
#define TURN_ON_LINE_SEVEN 11
#define WALK_LINE_SEVEN 12
#define STOP_ROBOT 19

/* Define the max intervals on black consecutively before we stop */
#define MAX_BLACK_INTERVAL 5

IRSensorMotorListener::IRSensorMotorListener(MovementControl *controller) {
    this->movementControl = controller;
    this->blackIntervalCount = 0;
}

void IRSensorMotorListener::updateSpeed(uint8_t s) {
    /* Tell the motor to change speed and store it locally */
    /* TODO: Should just add a retrieve in the motor controller */
    this->movementControl->setSpeed(s);
    this->speed = s;
}

void IRSensorMotorListener::updateDirection(Direction d) {
    /* Tell the motor to change direction and store it locally */
    /* TODO: Should just add a retrieve in the motor controller */
    this->movementControl->setDirection(d);
    this->direction = d;
}

void IRSensorMotorListener::walkLine(uint8_t rightData, uint8_t leftData) {

    /* Change the direction based on the sensor data */
    if (ISWHITE(rightData) && ISWHITE(leftData)) {
        /*
         * If both sensors are white then we are straddling the line and
         * and we can move forward again
         */
        this->updateDirection(Direction::RIGHT);

    } else if (ISBLACK(rightData) && ISWHITE(leftData)) {
        /*
         * If the right sensor is on black and the left is on white
         * we want to try and push the right sensor back to the white
         * so initiate a left turn
         */
        this->updateDirection(Direction::RIGHT);

    } else if (ISWHITE(rightData) && ISBLACK(leftData)) {
        /*
         * If the right sensor is on white and the left sensor
         * is on black we want to initiate a right turn to push the sensor
         * back onto the white
         */
        this->updateDirection(Direction::LEFT);
    }

    /*
     * If they are both on black the update code should be moving to a
     * new state so we will do nothing here
     */
}

void IRSensorMotorListener::update(uint8_t rightData, uint8_t leftData) {
    switch (this->currentStep) {
        case WALK_LINE_ONE: {
            /*
             * Step 0: Walk the first line
             * Change Event: Both sensors hit black line
             * Outcome: Initiate left turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the left turn and change state */
                this->updateDirection(Direction::LEFT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case TURN_ON_LINE_TWO: {
            /*
             * Step 1: Turn left onto line 2
             * Change Event: Both sensors hit white
             * Outcome: Begin walking line 2
             */
            delay(200);
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the left turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning */
            break;
        }
        case WALK_LINE_TWO: {
            /*
             * Step 2: Walk line 2 until we hit double black again
             * Change Event: Both sensors hit black
             * Outcome: Initiate right turn
             */
             if (ISBLACK(rightData) && ISBLACK(leftData)) {
                 /* Initiate the right turn and change state */
                 this->updateDirection(Direction::RIGHT);
                 this->currentStep++;
             } else {
                 /* Otherwise walk the line */
                 this->walkLine(rightData, leftData);
             }

            break;
        }
        case TURN_ON_LINE_THREE: {
            /*
             * Step 3: Turn right onto line 3
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 3
             */
            
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the right turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning onto line 3 */
            break;
        }
        case WALK_LINE_THREE: {
            /*
             * Step 4: Walk along line 3 until we hit double black
             * Change Event: Both sensors hit black
             * Outcome: Initiate right turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the right turn and change state */
                this->updateDirection(Direction::RIGHT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case TURN_ON_LINE_FOUR: {
            /*
             * Step 5: Turn right onto line 4
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 4
             */
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the right turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning onto line 4 */
            break;
        }
        case WALK_LINE_FOUR: {
            /*
             * Step 6: Walk along line 4 until we hit double black
             * Change Event: Both sensors hit black
             * Outcome: Initiate left turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the left turn and change state */
                this->updateDirection(Direction::LEFT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case TURN_ON_LINE_FIVE: {
            /*
             * Step 7: Turn left onto line 5
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 5
             */
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the right turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning onto line 5 */
            break;
        }
        case WALK_LINE_FIVE: {
            /*
             * Step 8: Walk along line 5 until we hit double black
             * Change Event: Both sensors hit black
             * Outcome: Initiate right turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the right turn and change state */
                this->updateDirection(Direction::RIGHT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case TURN_ON_LINE_SIX: {
            /*
             * Step 9: Turn right onto line 6
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 6
             */
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the right turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning onto line 6 */
            break;
        }
        case WALK_LINE_SIX: {
            /*
             * Step 10: Walk along line 6 until we hit double black
             * Change Event: Both sensors hit black
             * Outcome: Initiate right turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the right turn and change state */
                this->updateDirection(Direction::RIGHT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case TURN_ON_LINE_SEVEN: {
            /*
             * Step 11: Turn right onto line 7
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 7
             */
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the right turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning onto line 6 */
            break;
        }
        case WALK_LINE_SEVEN: {
            /*
             * Step 12: Walk down line seven until both sensors hit black
             * Change Event: Both sensors remain on black
             * Outcome: Initiate right turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the right turn and change state */
                this->updateDirection(Direction::RIGHT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;

        }
        case 13: {
            /*
             * Step 13: Turn right onto line 8
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 8
             */
            delay(200);
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the right turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning onto line 6 */
            break;
        }
        case 14: {
            /*
             * Step 14: Walk down line 8-9 until both sensors hit black
             * Change Event: Both sensors hit black
             * Outcome: Initiate left turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the right turn and change state */
                this->updateDirection(Direction::LEFT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case 15: {
            /*
             * Step 15: Turn right onto line 10
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 10
             */
            /* Change the direction based on the sensor data */
    if (ISWHITE(rightData) && ISWHITE(leftData)) {
        /*
         * If both sensors are white then we are straddling the line and
         * and we can move forward again
         */
        this->updateDirection(Direction::LEFT);

    } else if (ISBLACK(rightData) && ISWHITE(leftData)) {
        /*
         * If the right sensor is on black and the left is on white
         * we want to try and push the right sensor back to the white
         * so initiate a left turn
         */
        this->updateDirection(Direction::RIGHT);

    } else if (ISWHITE(rightData) && ISBLACK(leftData)) {
        /*
         * If the right sensor is on white and the left sensor
         * is on black we want to initiate a right turn to push the sensor
         * back onto the white
         */
        this->updateDirection(Direction::LEFT);
    } else if (ISBLACK(rightData) && ISBLACK(leftData)) {
        this->blackIntervalCount++;
        if (this->blackIntervalCount > 10) {
            this->updateSpeed(0);
        }
    }

            /* Otherwise keep turning onto line 6 */
            break;
        }
        case 16: {
            /*
             * Step 16: Walk down line 9 until both sensors hit black
             * Change Event: Both sensors hit black
             * Outcome: Initiate left turn
             */
            if (ISBLACK(rightData) && ISBLACK(leftData)) {
                /* Initiate the right turn and change state */
                this->updateDirection(Direction::LEFT);
                this->currentStep++;
            } else {
                /* Otherwise walk the line */
                this->walkLine(rightData, leftData);
            }

            break;
        }
        case 17: {
            /*
             * Step 17: Turn left onto line 10
             * Change Event: Both sensors hit white
             * Outcome: Begin walking on line 10
             */
            delay(100);
            if (ISWHITE(rightData) && ISWHITE(leftData)) {
                /* Stop the left turn and change state */
                this->walkLine(rightData, leftData);
                this->currentStep++;
            }

            /* Otherwise keep turning onto line 6 */
            break;
        }
        case 18: {
            this->walkLine(rightData, leftData);
            break;
        }
        case STOP_ROBOT: {
            /*
             * Step 13: Stop the robot
             * Change Event: None
             * Outcome: Robot should be complete maze
             */
            this->updateSpeed(0);

            /*
             * Instead of constantly setting the speed to 0 let's just
             * add one to the state which should be hitting the default
             * case and just breaking every time
             */
            this->currentStep++;
            break;
        }
        default: {
            /* There's not really anything we can do here */
            break;
        }
    }
}

char* IRSensorMotorListener::toString(char* buffer, size_t bufferSize) {
    snprintf(buffer,
	         bufferSize,
			 "IRSensorMotorListener[Direction=%d, Speed=%d, Step=%d, Controller=%p]",
			 this->direction, this->speed, this->currentStep, this->movementControl);

	return buffer;
}

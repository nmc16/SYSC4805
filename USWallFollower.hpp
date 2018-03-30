/**************************************************************
 * File: USWallFollower.hpp
 *
 * Description: Ultrasonic sensor listener that implements the
 *              wall follower algorithm.
 *
 * Author: Group 1
 **************************************************************/

/* Header Guard */
#ifndef USWALLFOLLOWER_H
#define USWALLFOLLOWER_H

/* Package Includes */
#include "USSensorListener.hpp"
#include "MovementControl.hpp"

class USWallFollower : public USSensorListener {
    public:
        USWallFollower(MovementControl* movementControl);

        void update(int8_t distances[], size_t distances_size);

    private:
        MovementControl* movementControl;
};

#endif
/**************************************************************
* File: USPledgeAlgorithm.hpp
*
* Description: Ultrasonic sensor listener that implements the
*              pledge algorithm.
*
* Author: Group 1
**************************************************************/

/* Header Guard */
#ifndef USPLEDGEALGORITHM_H
#define USPLEDGEALGORITHM_H

/* Standard Library Include */
#include <stdint.h>

/* Package Include */
#include "MovementControl.hpp"

class USPledgeAlgorithm {
	public:
	    USPledgeAlgorithm(MovementControl* movementControl);
		void update(int8_t distances[], size_t distances_size);

	private:
	    uint8_t findClosestDirection();
		void lhr(int8_t distances[], size_t distances_size);

	    MovementControl* movementControl;
		uint8_t currentOrientation;
		uint8_t forwardCount;
};

#endif

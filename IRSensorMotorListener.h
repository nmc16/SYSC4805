/**************************************************************
 * File: IRSensorMotorListener.h
 *
 * Description:
 *
 * Public Functions:
 *
 * @author Group 1
 **************************************************************/

#ifndef IRSensorMotorListener_h
#define IRSensorMotorListener_h

/* Standard Library Includes */
#include <Arduino.h>
#include <stdint.h>

/* Package Includes */
#include "MovementControl.hpp"
#include "IRSensorControl.h"

/* Class Definitions */
class IRSensorMotorListener : public IRListener {
	public:
        IRSensorMotorListener(MovementControl *controller);
        void update(uint8_t rightData, uint8_t leftData);
        char* toString(char* buffer, size_t bufferSize);

    private:
        void walkLine(uint8_t rightData, uint8_t leftData);
        void updateDirection(Direction d);
        void updateSpeed(uint8_t s);
        MovementControl *movementControl;
        uint8_t blackIntervalCount;
        uint8_t currentStep;
        uint8_t speed;
        Direction direction;
};

#endif // define

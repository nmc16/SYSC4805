/**************************************************************
 * File: MovementControl.h
 *
 * Description: Controls the speed and direction of the robot 
 *              through the 4 pins.
 *
 * Public Functions: void setSpeed(uint8_t)
 *                   void setDirection(Direction)
 *                   char* toString(char*, size_t)
 * 
 * @author Group 1
 * https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 **************************************************************/

#ifndef MovementControl_h
#define MovementControl_h

/* Includes */
#include <Arduino.h>
#include <stdint.h>
#include "IRSensorControl.h"

/* Enum Definitions */
enum Direction {FORWARD, BACKWARD, RIGHT, LEFT};

/* Class Definitions */
class MovementControl
{
    public:
	    /**
	     * Constructor.
		 * 
		 * @param A_IA Pin number for motor A speed control
		 * @param A_IB Pin number for motor A direction control
		 * @param B_IA Pin number for motor B speed control
		 * @param B_IB Pin number for motor B direction control
	     */
	    MovementControl(uint8_t A_IA, uint8_t A_IB, uint8_t B_IA, uint8_t B_IB);

		/**
		 * Set the speed level between 0-10. 
		 * 
		 * A speed of 0 will shut off the motors, 10 is the max speed.
		 * 
		 * @param speedLevel Number between 0 and 10 to set the motor speed to
		 */
		void setSpeed(uint8_t speedLevel);

		/**
		 * Sets the direction of the motors.
		 * 
		 * Right/left will pivot in place towards that direction.
		 * 
		 * @param direction Direction the robot should begin to move
		 */
		void setDirection(Direction direction);

		/**
		 * Writes the string representation of the motor state to the buffer.
		 * 
		 * Warning: This will require a large amount of memory. Should only
		 *          be used for debugging.
		 * 
		 * @param buffer Character buffer to write the string to
		 * @param buffer_size Max size of the buffer
		 */
		char* toString(char* buffer, size_t buffer_size);

    private:
		/* Pins that represent the speed and direction of the motor */
		uint8_t pinASpeed;
		uint8_t pinADirection;
		uint8_t pinBSpeed;
		uint8_t pinBDirection;

		/* The speed and direction of each motor */
		uint8_t motorRightSpeed;
		uint8_t motorRightDirection;
		uint8_t motorLeftSpeed;
		uint8_t motorLeftDirection;
		uint8_t currentSpeedLevel;
		Direction currentDirection;

		/**
		 * Updates the motor
		 */ 
		void updateMotor();
};

#endif // define


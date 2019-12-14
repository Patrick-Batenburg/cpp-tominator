#pragma once
#include "Claw.h"

class RobotArm
{
private:
	int xPulsePin;
	int xDirectionPin;
	int yPulsePin;
	int yDirectionPin;
	int zPulsePin;
	int zDirectionPin;
	int x;
	int y;
	int z;
	int minimumBoundary;
	int maximumXBoundary;
	int maximumYBoundary;
	Claw claw;

public:
	/**
		Initializes a new instance of the RobotArm class.
	*/
	RobotArm();
	
	/**
		Initializes a new instance of the RobotArm class.

		@param xPulsePin		The robot arm's X-axis stepper motor pulse pin.
		@param xDirectionPin	The robot arm's X-axis stepper motor direction pin.
		@param yPulsePin		The robot arm's Y-axis stepper motor pulse pin.
		@param yDirectionPin	The robot arm's Y-axis stepper motor direction pin.
		@param zPulsePin		The robot arm's Z-axis stepper motor pulse pin.
		@param zDirectionPin	The robot arm's Z-axis stepper motor direction pin.
		@param claw				The claw object.
	*/
	RobotArm(int xPulsePin, int xDirectionPin, int yPulsePin, int yDirectionPin, int zPulsePin, int zDirectionPin, Claw claw);

	/**
		Initializes a new instance of the RobotArm class.

		@param xPulsePin		The robot arm's X-axis stepper motor pulse pin.
		@param xDirectionPin	The robot arm's X-axis stepper motor direction pin.
		@param yPulsePin		The robot arm's Y-axis stepper motor pulse pin.
		@param yDirectionPin	The robot arm's Y-axis stepper motor direction pin.
		@param zPulsePin		The robot arm's Z-axis stepper motor pulse pin.
		@param zDirectionPin	The robot arm's Z-axis stepper motor direction pin.
		@param clawPulsePin		The claw's stepper motor pulse pin.
		@param clawDirectionPin The claw's stepper motor direction pin.
	*/
	RobotArm(int xPulsePin, int xDirectionPin, int yPulsePin, int yDirectionPin, int zPulsePin, int zDirectionPin, int clawPulsePin, int clawDirectionPin);

	/**
		Deconstruct the instance of the RobotArm class.
	*/
	~RobotArm();
	
	/**
		Handles the X, Y and Z-axis of the robot arm.
	*/
	void HandleArm(int x, int y, int z);

	/**
		Opens the claw.
	*/
	void OpenClaw();

	/**
		Closes the claw.
	*/
	void CloseClaw();

	/**
		Gets the X-axis.

		@return The X-axis.
	*/
	int GetXAxis();

	/**
		Sets the X-axis.

		@param value The X-axis.
	*/
	void SetXAxis(int value);

	/**
		Gets the Y-axis.

		@return The Y-axis.
	*/
	int GetYAxis();

	/**
		Sets the Y-axis.

		@param value The Y-axis.
	*/
	void SetYAxis(int value);

	/**
		Gets the Z-axis.

		@return The Z-axis.
	*/
	int GetZAxis();

	/**
		Sets the Z-axis.

		@param value The Z-axis.
	*/
	void SetZAxis(int value);

private:
	/**
		Checks whenever the specified value is out of bounds.

		@param value The X-axis value to check.
		@return The same value if not out of bounds. If out of bounds, the nearest minimum or maximum value is returned instead.
	*/
	int CheckXAxisBoundary(int value);
	/**
		Checks whenever the specified value is out of bounds.

		@param value The Y-axis value to check.
		@return The same value if not out of bounds. If out of bounds, the nearest minimum or maximum value is returned instead.
	*/
	int CheckYAxisBoundary(int value);
};

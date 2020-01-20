#pragma once
#include "Claw.h"

class RobotArm
{
private:
	static const int motorStepsGridY = 923;
	static const int motorStepsZ = 800;
	static const int motorStepsSortZ = 1200;
	static const int motorStepsConveyorBelt = 675;
	static const int motorStepsConveyorBeltX = 655;
	static const int motorStepsConveyorXOffset = 450;
	static const int motorStepsColumnZeroOffset = 200;
	static const int motorStepsGridZ = 2333;
	static const int delay = 1500;
	static const int delayZAxis = 500;
	int xPulsePin;
	int xDirectionPin;
	int xHomingPin;
	int yPulsePin;
	int yDirectionPin;
	int yHomingPin;
	int zPulsePin;
	int zDirectionPin;
	int zHomingPin;
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
		@param xHomingPin		The robot arm's X-axis homing pin.
		@param yPulsePin		The robot arm's Y-axis stepper motor pulse pin.
		@param yDirectionPin	The robot arm's Y-axis stepper motor direction pin.
		@param yHomingPin		The robot arm's Y-axis homing pin.
		@param zPulsePin		The robot arm's Z-axis stepper motor pulse pin.
		@param zDirectionPin	The robot arm's Z-axis stepper motor direction pin.
		@param zHomingPin		The robot arm's Z-axis homing pin.
		@param claw				The claw object.
	*/
	RobotArm(int xPulsePin, int xDirectionPin, int xHomingPin, int yPulsePin, int yDirectionPin, int yHomingPin, int zPulsePin, int zDirectionPin, int zHomingPin, Claw claw);

	/**
		Deconstruct the instance of the RobotArm class.
	*/
	~RobotArm();
	
	/**
		Handles the X, Y and Z-axis of the robot arm.
	*/
	void HandleArm(int x, int y, int z);
	
	/**
		Applies homing to the robot arm. By default it will home the X, Y, Z-axis and the claw.
		
		@param homeWhat Indicates what individual component needs homing based on int-value.
		0 = Homing is applied to the the X, Y, Z-axis and claw (default).
		1 - Homing is only applied to the X, Y, and Z-axis.
		2 - Homing is only applied to the X-axis.
		3 - Homing is only applied to the Y-axis.
		4 = Homing is only applied to the Z-axis.
		5 = Homing is only applied to the claw.
	*/
	void Home(int homeWhat = 0);

	/**
		Applies homing o the X-axis.
	*/
	void HomeXAxis();

	/**
		Applies homing o the Y-axis.
	*/
	void HomeYAxis();

	/**
		Applies homing o the Z-axis.
	*/
	void HomeZAxis();

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

	/**
		Gets the claw object.

		@return The claw object.
	*/
	Claw GetClaw();

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

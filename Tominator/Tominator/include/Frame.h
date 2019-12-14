#pragma once
#include "UltrasonicSensor.h"
#include "DCMotor.h"
#include "Grid.h"
#include "ConveyorBelt.h"

class Frame
{
private:
	DCMotor dcMotor;
	int in2DirectionPin;
	int pwmPin;
	int reedGridSidePin;
	int reedSortingSidePin;
	UltrasonicSensor gridSideUltrasonicSensor;
	UltrasonicSensor sortingSideUltrasonicSensor;
	Grid* grid;
	ConveyorBelt* conveyorBelt;
public:
	/**
		Initializes a new instance of the Frame class.
	*/
	Frame();

	/**
		Initializes a new instance of the Frame class.
		
		@param dcMotor						The DC motor object.
		@param gridSideUltrasonicSensor		The ultrasonic sensor object located at the grid side.
		@param sortingSideUltrasonicSensor	The ultrasonic sensor object located at the sorting side.
		@param reedGridSidePin				The reed contact located at the grid side.
		@param reedSortingSidePin			The reed contact located at the sorting side.
		@param grid							The grid pointer object for relation data.
		@param conveyorBelt					The conveyor belt pointer for relation data.
	*/
	Frame(DCMotor dcMotor, UltrasonicSensor gridSideUltrasonicSensor, UltrasonicSensor sortingSideUltrasonicSensor, int reedGridSidePin, int reedSortingSidePin, Grid* grid, ConveyorBelt* conveyorBelt);
	
	/**
		Deconstruct the instance of the Frame class.
	*/
	~Frame();

	/**
		Handles the DC motor in conjunction with ultrasonic sensors and reed contacts. The DC motor has a smooth stop to prevent it from smashing/crashing into the frame itself.
		
		@param direction The direction the DC motor is spinning into. DirectionType::Forward = go to sorting side. DirectionType::Reverse = go to grid side.
	*/	
	void HandleDCMotor(DirectionType direction);

	/**
		Handles the DC motor offset. The frame should be at either the grid or sorting side by know. Depending on a couple variables an offset needs to be made in some cases.
		
		@param direction The direction the DC motor is spinning into. DirectionType::Forward = is at sorting side. DirectionType::Reverse = is at grid side.
	*/	
	void HandleDCMotorOffset(DirectionType direction);

	/**
		Gets the DC motor object.
		
		@return The DC motor object.
	*/
	DCMotor GetDCMotor();
};

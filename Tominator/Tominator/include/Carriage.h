#pragma once
#include "DCMotor.h"

class Carriage
{
private:
	DCMotor* dcMotor;
	int hallSensorTopPin;
	int hallSensorMiddlePin;
	int hallSensorBottomPin;
	
public:
	/**
		Initializes a new instance of the Carriage class.
	*/
	Carriage();

	/**
		Initializes a new instance of the Carriage class.

		@param dcMotor				The DC motor object.
		@param hallSensorBottomPin	The hall sensor bottom pin.
		@param hallSensorMiddlePin	The hall sensor middle pin.
		@param hallSensorTopPin		The hall sensor top pin.
	*/
	Carriage(DCMotor* dcMotor, int hallSensorBottomPin, int hallSensorMiddlePin, int hallSensorTopPin);

	/**
		Deconstruct the instance of the Carriage class.
	*/
	~Carriage();

	/**
		Handles the DC motor. The DC motor can only run when the carriage is not yet at the right height and a motor was turned on.
		@param speedPercentage	The speed in percentage.
		@param goToHallSensor	The hall sensor to reach and read output from.
	*/
	void HandleDCMotor(int speedPercentage, int goToHallSensor);

	/**
		Makes the carriage return to its default position, which is at the bottom.
	*/	
	void Home();	

	/**
		Gets the DC motor object.
		
		@return The DC motor object.
	*/
	DCMotor* GetDCMotor();
};

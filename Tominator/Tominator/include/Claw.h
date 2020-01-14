#pragma once

class Claw
{
private:
	int pulsePin;
	int directionPin;
	int homingPin;
	static const int delay = 800;
	static const int motorSteps = 1800;

public:
	/**
		Initializes a new instance of the Claw class.
	*/
	Claw();
	
	/**
		Initializes a new instance of the Claw class.

		@param pulsePin		The claw's stepper motor pulse pin.
		@param directionPin The claw's stepper motor direction pin.
		@param homingPin	The claw's homing pin.
	*/
	Claw(int pulsePin, int directionPin, int homingPin);

	/**
		Deconstruct the instance of the Claw class.
	*/
	~Claw();

	/**
		Opens the claw.
	*/	
	void Open();	

	/**
		Closes the claw.
	*/
	void Close();

	/**
		Gets the pulse pin.
		
		@return The pulse pin.
	*/
	int GetPulsePin();

	/**
		Gets the direction pin.
		
		@return The direction pin.
	*/
	int GetDirectionPin();

	/**
		Gets the homing pin.
		
		@return The homing pin.
	*/
	int GetHomingPin();
	
private:

	/**
		Handles the stepper motor by making it run.
	*/
	void HandleStepper();
};

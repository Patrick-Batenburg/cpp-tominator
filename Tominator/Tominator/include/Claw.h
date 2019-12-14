#pragma once

class Claw
{
private:
	int pulsePin;
	int directionPin;
	
public:
	/**
		Initializes a new instance of the Claw class.
	*/
	Claw();
	
	/**
		Initializes a new instance of the Claw class.

		@param pulsePin		The claw's stepper motor pulse pin.
		@param directionPin The claw's stepper motor direction pin.
	*/
	Claw(int pulsePin, int directionPin);

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
private:

	/**
		Handles the stepper motor by making it run.
	*/
	void HandleStepper();
};

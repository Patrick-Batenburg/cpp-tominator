#pragma once
#include <Arduino.h>

class RotaryEncoder
{
private:
	int clkPin;
	int dtPin;
	int counter;
	byte state;
public:
	/**
		Initializes a new instance of the RotaryEncoder class.
	*/
	RotaryEncoder();

	/**
		Initializes a new instance of the RotaryEncoder class.
	*/
	RotaryEncoder(int clkPin, int dtPin);

	/**
		Deconstruct the instance of the RotaryEncoder class.
	*/
	~RotaryEncoder();

	/**
		Determines whenever or not a rotation left or right occurred and updates the counter accordingly.
	*/
	void CheckStateChange();

	/**
		Gets the amount of times when there was counted forward or backwards.
		
		@return The amount of times when there was counted forward or backwards.
	*/
	int GetCounter();
};
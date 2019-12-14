#pragma once

class UltrasonicSensor
{
private:
	int triggerPin;
	int echoPin;
public:
	/**
		Initializes a new instance of the UltrasonicSensor class.
	*/
	UltrasonicSensor();

	/**
		Initializes a new instance of the UltrasonicSensor class.

		@param triggerPin	The ultrasonics sensor trigger pin.
		@param echoPin		The ultrasonics sensor echo pin.
	*/
	UltrasonicSensor(int triggerPin, int echoPin);
	
	/**
		Deconstruct the instance of the UltrasonicSensor class.
	*/
	~UltrasonicSensor();
	
	/**
		Gets the trigger pin.
		
		@return The trigger pin.
	*/
	int GetTriggerPin();

	/**
		Gets the echo pin.
		
		@return The echo pin.
	*/
	int GetEchoPin();
};

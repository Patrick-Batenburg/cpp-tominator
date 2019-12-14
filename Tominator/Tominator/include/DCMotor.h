#pragma once
#include <Arduino.h>

/**
	Types of directions a DC motor can spin into.
*/
enum DirectionType
{
	Reverse,
	Forward
};

class DCMotor
{
private:
	int in1DirectionPin;
	int in2DirectionPin;
	int pwmPin;
	int speed;

public:
	/**
		Initializes a new instance of the DCMotor class.
		Starts by default in the forward direction with 0% speed.
	*/
	DCMotor();
	
	/**
		Initializes a new instance of the DCMotor class.
		Starts by default in the forward direction with 0% speed.
		
		@param in1DirectionPin	The IN1 direction pin.
		@param in2DirectionPin	The IN2 direction pin.
		@param pwmPin			The pulse width modulation pin.
	*/
	DCMotor(int in1DirectionPin, int in2DirectionPin, int pwmPin);

	/**
		Deconstruct the instance of the DCMotor class.
	*/
	~DCMotor();
	
	/**
		Makes the DC motor start in the specified direction.

		@param direction The direction the DC motor starts in.
	*/
	void Start(DirectionType direction);

	/**
		Makes the DC motor stop.
	*/
	void Stop();

	/**
		Makes the DC motor run.
		@param delayInMilliseconds The delay in milliseconds that is needed for pulse width modulation. Default value is 30 milliseconds.
	*/
	void Run(int delayInMilliseconds = 30);

	/**
		Makes the DC motor brake and let it stop quickly.
	*/
	void Brake();
    
	/**
		Makes the DC motor do a smooth start in the specified direction and time.

		@param direction The direction the DC motor starts in.
		@param speedPrecentage The motor speed between 0 - 100%.
		@param timeInSeconds The time in seconds to do a smooth start. Default = 5 seconds.
	*/
	void SoftStart(DirectionType direction, int speedPrecentage, int timeInSeconds = 5);
    
	/**
		Makes the DC motor do a smooth stop in the specified time.

		@param timeInSeconds The time in seconds to do a smooth stop. Default = 5 seconds.
	*/
	void SmoothStop(int timeInSeconds = 5);
    
	/**
		Sets the motor speed between 0 and 255.

		@param speed The speed.
	*/
	void SetSpeed(int speed);
    
	/**
		Sets the motor speed between 0 - 100%.

		@param percentage The percentage.
	*/
	void SetSpeedInPercentage(int percentage);
private:
	/**
		Makes the DC motor start in the forward direction.
	*/
    void Forward();

	/**
		Makes the DC motor start in the reverse direction.
	*/
    void Reverse();
};

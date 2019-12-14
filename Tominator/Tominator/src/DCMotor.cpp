#include "DCMotor.h"
#include <Arduino.h>

DCMotor::DCMotor()
{
	this->Forward();
	this->SetSpeed(0);
}

 DCMotor::DCMotor(int in1DirectionPin, int in2DirectionPin, int pwmPin) : DCMotor()
 {
	this->in1DirectionPin = in1DirectionPin;
	this->in2DirectionPin = in2DirectionPin;
	this->pwmPin = pwmPin;
 }

DCMotor::~DCMotor()
{
}

void DCMotor::Start(DirectionType direction)
{
    if(direction == DirectionType::Forward)
    {
		this->Forward();
	}
	else
	{
		this->Reverse();
	}
}

void DCMotor::Stop()
{
    digitalWrite(this->in1DirectionPin, LOW);
    digitalWrite(this->in2DirectionPin, LOW);
}

void DCMotor::Run(int delayInMilliseconds)
{
	analogWrite(this->pwmPin, this->speed);
	delay(delayInMilliseconds);
}

void DCMotor::Brake()
{
    digitalWrite(this->in1DirectionPin, HIGH);
    digitalWrite(this->in2DirectionPin, HIGH);
}

void DCMotor::SoftStart(DirectionType direction, int speedPrecentage, int timeInSeconds)
{
	this->Start(direction);
	SetSpeedInPercentage(speedPrecentage);
	int delay = timeInSeconds * 1000 / this->speed;
	
	for(int i = 0; i < this->speed; i++)
	{
		this->Run(delay);
	}
}

void DCMotor::SmoothStop(int timeInSeconds)
{
	int delay = timeInSeconds * 1000 / this->speed;

	for(int i = this->speed; i > 0; i--)
	{
		this->Run(delay);
	}
	
	this->Stop();
}

void DCMotor::SetSpeed(int speed)
{
	if (speed < 0)
	{
		speed = 0;
	}
	else if (speed > 255)
	{
		speed = 255;
	}	
	
    this->speed = speed;
}

void DCMotor::SetSpeedInPercentage(int percentage)
{
	if (percentage < 0)
	{
		percentage = 0;
	}
	else if (percentage > 100)
	{
		percentage = 100;
	}
	
	this->speed = map(percentage, 0, 100, 0, 255);
}

void DCMotor::Forward()
{
	digitalWrite(this->in1DirectionPin, HIGH);
	digitalWrite(this->in2DirectionPin, LOW);
}

void DCMotor::Reverse()
{
	digitalWrite(this->in1DirectionPin, LOW);
	digitalWrite(this->in2DirectionPin, HIGH);
}

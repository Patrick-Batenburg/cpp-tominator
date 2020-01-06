#include "Claw.h"
#include <Arduino.h>

Claw::Claw()
{
}

Claw::Claw(int pulsePin, int directionPin, int homingPin) : Claw()
{
	this->pulsePin = pulsePin;
	this->directionPin = directionPin;
	this->homingPin = homingPin;
	pinMode(this->pulsePin, OUTPUT);
	pinMode(this->directionPin, OUTPUT);
	pinMode(this->homingPin, INPUT);
}

Claw::~Claw()
{
}

void Claw::Open()
{
	digitalWrite(this->directionPin, HIGH);
	HandleStepper();
}

void Claw::Close()
{
	digitalWrite(this->directionPin, LOW);
	HandleStepper();
}

void Claw::Home()
{
	bool reachedEnd = false;
	digitalWrite(this->directionPin, HIGH);
	
	while (!reachedEnd)
	{
		if (digitalRead(this->homingPin) == LOW)
		{
			digitalWrite(this->pulsePin, HIGH);
			delayMicroseconds(400);
			digitalWrite(this->pulsePin, LOW);
			delayMicroseconds(400);
		}

		// If the homing pin is HIGH then we successfully managed to return back to the default position.
		if (digitalRead(this->homingPin) == HIGH)
		{
			reachedEnd = true;
		}
	}
}

int Claw::GetPulsePin()
{
	return this->pulsePin;
}

int Claw::GetDirectionPin()
{
	return this->directionPin;
}

int Claw::GetHomingPin()
{
	return this->homingPin;
}

void Claw::HandleStepper()
{
	digitalWrite(this->pulsePin, HIGH);
	delayMicroseconds(400);
	digitalWrite(this->pulsePin, LOW);
	delayMicroseconds(400);
}

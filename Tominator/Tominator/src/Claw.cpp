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
	
	while (true)
	{
		// If the homing pin is LOW then we successfully managed to return back to the default position. The claw is open.
		if (digitalRead(this->homingPin) == LOW)
		{
			break;
		}
		else if (digitalRead(this->homingPin))
		{
			digitalWrite(this->pulsePin, HIGH);
			delayMicroseconds(delay);
			digitalWrite(this->pulsePin, LOW);
			delayMicroseconds(delay);
		}
	}
}

void Claw::Close()
{
	digitalWrite(this->directionPin, LOW);

	for (int i = 0; i < motorSteps; i++)
	{
		digitalWrite(this->pulsePin, HIGH);
		delayMicroseconds(delay);
		digitalWrite(this->pulsePin, LOW);
		delayMicroseconds(delay);
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

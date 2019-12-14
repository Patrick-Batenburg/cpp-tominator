#include "Claw.h"
#include <Arduino.h>

Claw::Claw()
{
}

Claw::Claw(int pulsePin, int directionPin) : Claw()
{
	this->pulsePin = pulsePin;
	this->directionPin = directionPin;
	
	pinMode(this->pulsePin, OUTPUT);
	pinMode(this->directionPin, OUTPUT);
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

void Claw::HandleStepper()
{
	digitalWrite(this->pulsePin, HIGH);
	delayMicroseconds(400);
	digitalWrite(this->pulsePin, LOW);
	delayMicroseconds(400);
}

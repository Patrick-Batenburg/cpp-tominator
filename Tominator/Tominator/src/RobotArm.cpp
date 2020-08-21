#include "RobotArm.h"
#include "TominatorPins.h"
#include <Arduino.h>

RobotArm::RobotArm()
{
	this->x = new int(0);
	this->y = new int(0);
	this->z = new int(0);
	this->minimumBoundary = 0;
	this->maximumXBoundary = 3;
	this->maximumYBoundary = 2;
}

RobotArm::RobotArm(int xPulsePin, int xDirectionPin, int xHomingPin, int yPulsePin, int yDirectionPin, int yHomingPin, int zPulsePin, int zDirectionPin, int zHomingPin, Claw claw) : RobotArm()
{
	this->xPulsePin = xPulsePin;
	this->xDirectionPin = xDirectionPin;
	this->xHomingPin = xHomingPin;
	this->yPulsePin = yPulsePin;
	this->yDirectionPin = yDirectionPin;
	this->yHomingPin = yHomingPin;
	this->zPulsePin = zPulsePin;
	this->zDirectionPin = zDirectionPin;
	this->zHomingPin = zHomingPin;
	this->claw = claw;

	pinMode(this->xPulsePin, OUTPUT);
	pinMode(this->xDirectionPin, OUTPUT);
	pinMode(this->xHomingPin, INPUT);
	pinMode(this->yPulsePin, OUTPUT);
	pinMode(this->yDirectionPin, OUTPUT);
	pinMode(this->yHomingPin, INPUT);
	pinMode(this->zPulsePin, OUTPUT);
	pinMode(this->zDirectionPin, OUTPUT);
	pinMode(this->zHomingPin, INPUT);
}

RobotArm::~RobotArm()
{
}

// Conveyor belt positions:
// x:3 y:0		x:3 y:1		x:3 y:2
// x:2 y:0		x:2 y:1		x:2 y:2
// x:1 y:0		x:1 y:1		x:1 y:2
//
// Grid row. Default (home) position = x:0 y:0
// x:0 y:0		x:0 y:1		x:0 y:2
void RobotArm::HandleXAxis(int newX)
{
	int steps = 0;
	int difference = 0;
	newX = CheckXAxisBoundary(newX);

	if (this->GetXAxis() < newX)
	{
		digitalWrite(this->xDirectionPin, HIGH);
	}
	else
	{
		digitalWrite(this->xDirectionPin, LOW);
	}

	if (this->GetXAxis() > 0 && newX == 0) // If going from the conveyor belt to the grid then homing has the same result.
	{
		this->HomeXAxis();
	}
	else if (this->GetXAxis() != newX)
	{
		difference = abs(newX - this->GetXAxis());
		steps = difference * motorStepsX;

		if (this->GetXAxis() == 0 && newX > 0)
		{
			steps += motorStepsOffsetX;
		}

		while (steps > 0)
		{
			steps--;
			digitalWrite(this->xPulsePin, HIGH);
			delayMicroseconds(delay);
			digitalWrite(this->xPulsePin, LOW);
			delayMicroseconds(delay);
		}

		this->SetXAxis(newX);
	}
}

void RobotArm::HandleYAxis(int newY)
{
	int steps = 0;
	int difference = 0;
	newY = CheckYAxisBoundary(newY);

	if (this->GetYAxis() < newY)
	{
		digitalWrite(this->yDirectionPin, LOW);
	}
	else
	{
		digitalWrite(this->yDirectionPin, HIGH);
	}

	if (this->GetYAxis() != newY)
	{
		difference = abs(newY - this->GetYAxis());
		steps = difference * motorStepsY;

		while (steps > 0)
		{
			steps--;
			digitalWrite(this->yPulsePin, HIGH);
			delayMicroseconds(delay);
			digitalWrite(this->yPulsePin, LOW);
			delayMicroseconds(delay);
		}

		this->SetYAxis(newY);
	}
}

void RobotArm::HandleZAxis(int newZ, int extraSteps, int lessSteps)
{
	int steps = extraSteps - lessSteps;
	int difference = 0;

	if (this->GetZAxis() > newZ)
	{
		digitalWrite(this->zDirectionPin, LOW);
	}
	else
	{
		digitalWrite(this->zDirectionPin, HIGH);
	}

	if (this->GetZAxis() != newZ)
	{
		difference = abs(newZ - this->GetZAxis());
		steps += difference * motorStepsZ;

		while (steps > 0)
		{
			steps--;
			digitalWrite(this->zPulsePin, HIGH);
			delayMicroseconds(delayZAxis);
			digitalWrite(this->zPulsePin, LOW);
			delayMicroseconds(delayZAxis);
		}

		this->SetZAxis(newZ);
	}
}

void RobotArm::HandleZAxisOffset(int steps, uint8_t direction)
{
	digitalWrite(this->zDirectionPin, direction);
	
	while (steps > 0)
	{
		steps--;
		digitalWrite(this->zPulsePin, HIGH);
		delayMicroseconds(delayZAxis);
		digitalWrite(this->zPulsePin, LOW);
		delayMicroseconds(delayZAxis);
	}
}

void RobotArm::HandleYAxisOffset(DirectionType direction, int offset)
{
	int steps = motorStepsOffsetY + offset;
	
	if (direction == DirectionType::Forward)
	{
		digitalWrite(this->yDirectionPin, LOW);
	}
	else
	{
		digitalWrite(this->yDirectionPin, HIGH);		
	}

	while (steps > 0)
	{
		steps--;
		digitalWrite(this->yPulsePin, HIGH);
		delayMicroseconds(delay);
		digitalWrite(this->yPulsePin, LOW);
		delayMicroseconds(delay);
	}
}

void RobotArm::Home(int homeWhat)
{
	switch (homeWhat)
	{
		default:
		case 0:
			this->HomeXAxis();
			this->HomeYAxis();
			this->HomeZAxis();
			this->OpenClaw();
			break;
		case 1:
			this->HomeXAxis();
			this->HomeYAxis();
			this->HomeZAxis();
			break;
		case 2:
			this->HomeXAxis();
			break;
		case 3:
			this->HomeYAxis();
			break;
		case 4:
			this->HomeZAxis();
			break;
		case 5:
			this->OpenClaw();
			break;
	}
}

void RobotArm::HomeXAxis()
{
	// Set direction from the conveyor belt to the grid.
	digitalWrite(this->xDirectionPin, LOW);

	while (true)
	{
		// If the homing pin is LOW then we successfully managed to return back to the default position.
		if (digitalRead(this->xHomingPin) == LOW)
		{
			this->SetXAxis(0);
			break;
		}
		else if (digitalRead(this->xHomingPin))
		{
			digitalWrite(this->xPulsePin, HIGH);
			delayMicroseconds(this->delay);
			digitalWrite(this->xPulsePin, LOW);
			delayMicroseconds(this->delay);
		}
	}
}

void RobotArm::HomeYAxis()
{
	// Set direction from right to left.
	digitalWrite(this->yDirectionPin, HIGH);

	while (true)
	{
		// If the homing pin is LOW then we successfully managed to return back to the default position.
		if (digitalRead(this->yHomingPin) == LOW)
		{
			this->SetYAxis(0);
			break;
		}
		else if (digitalRead(this->yHomingPin))
		{
			digitalWrite(this->yPulsePin, HIGH);
			delayMicroseconds(this->delay);
			digitalWrite(this->yPulsePin, LOW);
			delayMicroseconds(this->delay);
		}
	}
}

void RobotArm::HomeZAxis()
{
	// Set direction from bottom to top.
	digitalWrite(this->zDirectionPin, LOW);

	while (true)
	{
		// If the homing pin is LOW then we successfully managed to return back to the default position.
		if (digitalRead(this->zHomingPin) == LOW)
		{
			this->SetZAxis(0);
			break;
		}
		else if (digitalRead(this->zHomingPin))
		{
			digitalWrite(this->zPulsePin, HIGH);
			delayMicroseconds(this->delayZAxis);
			digitalWrite(this->zPulsePin, LOW);
			delayMicroseconds(this->delayZAxis);
		}
	}
}

void RobotArm::OpenClaw()
{
	this->claw.Open();
}

void RobotArm::CloseClaw()
{
	this->claw.Close();
}

int RobotArm::GetXAxis()
{
	return *this->x;
}

void RobotArm::SetXAxis(int value)
{
	*this->x = value;
}

int RobotArm::GetYAxis()
{
	return *this->y;
}

void RobotArm::SetYAxis(int value)
{
	*this->y = value;
}

int RobotArm::GetZAxis()
{
	return *this->z;
}

void RobotArm::SetZAxis(int value)
{
	*this->z = value;
}

Claw RobotArm::GetClaw()
{
	return this->claw;
}

int RobotArm::CheckXAxisBoundary(int value)
{
	if (value > maximumXBoundary)
	{
		value = maximumXBoundary;
	}
	else if (value < minimumBoundary)
	{
		value = minimumBoundary;
	}

	return value;
}

int RobotArm::CheckYAxisBoundary(int value)
{
	if (value > maximumYBoundary)
	{
		value = maximumYBoundary;
	}
	else if (value < minimumBoundary)
	{
		value = minimumBoundary;
	}

	return value;
}

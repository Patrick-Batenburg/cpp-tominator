#include "RobotArm.h"
#include "TominatorPins.h"
#include <Arduino.h>

RobotArm::RobotArm()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
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

void RobotArm::HandleArm(int newX, int newY, int newZ)
{
	// Conveyor belt positions:
	// x:3 y:0		x:3 y:1		x:3 y:2
	// x:2 y:0		x:2 y:1		x:2 y:2
	// x:1 y:0		x:1 y:1		x:1 y:2
	//
	// Grid row. Default position = x:0 y:0
	// x:0 y:0		x:0 y:1		x:0 y:2
	
	// Set direction from the grid to the conveyor belt.
	// X from bottom (x:0) to top (x:3), Y from left (y:0) to right (y:2), Z from up to down.
	digitalWrite(this->xDirectionPin, HIGH);
	digitalWrite(this->yDirectionPin, HIGH);
	digitalWrite(this->zDirectionPin, HIGH);
	
	// Check robot arm boundaries.
	newX = CheckXAxisBoundary(newX);
	newY = CheckYAxisBoundary(newY);
	
	// Calculate new X, Y and Z-axis.
	newX -= this->GetXAxis();
	newY -= this->GetYAxis();
	newZ -= this->GetZAxis();
	
	// If newX or newY are negative values then this mean go into the opposite direction,
	// after that take the absolute values of newX or newY.
	// Example go from the conveyor belt to the grid:
	// newX = 0, this->GetXAxis() = 3.
	// 0 - 3 = -3 = go form top (x:3) to bottom (x:0).
	if (newX < 0)
	{
		digitalWrite(this->xDirectionPin, LOW);		
		newX = abs(newX);
	}
	
	if (newY < 0)
	{
		digitalWrite(this->yDirectionPin, LOW);
		newY = abs(newY);
	}
	
	// If newZ is negative then the claw must go down, otherwise if positive me
	if (newZ < 0)
	{
		newZ = abs(newZ);
	}
	else
	{
		digitalWrite(this->zDirectionPin, LOW);
	}

	this->SetXAxis(newX);
	this->SetYAxis(newY);
	this->SetYAxis(newZ);
	
	int steps = 455;
	int stepsX = this->GetXAxis() * steps;
	int stepsY = this->GetYAxis() * steps;
	int stepsZ = this->GetZAxis() * steps;
	bool reachedEnd = false;

	// Handle X and Y-axis movement simultaneously with digitalWrite().
	while (!reachedEnd)
	{
		if (stepsX > 0)
		{
			stepsX--;
			digitalWrite(this->xPulsePin, HIGH);
		}
		
		if (stepsY > 0)
		{
			stepsY--;
			digitalWrite(this->yPulsePin, HIGH);
		}
		
		if (stepsX > 0 || stepsY > 0)
		{
			// If both X and Y-axis are called with digitalWrite() before a delay will make diagnonal movement possible.
			delayMicroseconds(400);		
			digitalWrite(this->xPulsePin, LOW);
			digitalWrite(this->yPulsePin, LOW);
			delayMicroseconds(400);
		}
		
		// Handle Z-axis movement as last
		if (stepsX == 0 && stepsY == 0)
		{
			if (stepsZ > 0)
			{
				stepsZ--;
				digitalWrite(this->zPulsePin, HIGH);
				delayMicroseconds(400);
				digitalWrite(this->zPulsePin, LOW);
				delayMicroseconds(400);
			}
			else
			{
				reachedEnd = true;
			}
		}
	}
}

void RobotArm::Home()
{
//REED6_HOMING_Y 37
//REED7_HOMING_X 38
//REED8_HOMING_Z 39
//REED9_HOMING_CLAW

	// Conveyor belt positions:
	// x:3 y:0		x:3 y:1		x:3 y:2
	// x:2 y:0		x:2 y:1		x:2 y:2
	// x:1 y:0		x:1 y:1		x:1 y:2
	//
	// Grid row. Default position = x:0 y:0
	// x:0 y:0		x:0 y:1		x:0 y:2

	bool reachedEnd = false;

	// Set direction from the conveyor belt to the grid. From top to bottom, from right to left.
	digitalWrite(this->xDirectionPin, LOW);
	digitalWrite(this->yDirectionPin, LOW);
	digitalWrite(this->zDirectionPin, LOW);

	// Handle X, Y and Z-axis movement simultaneously with digitalWrite().
	while (!reachedEnd)
	{
		if (digitalRead(this->xHomingPin) == LOW)
		{
			digitalWrite(this->xPulsePin, HIGH);
		}
	
		if (digitalRead(this->yHomingPin) == LOW)
		{
			digitalWrite(this->yPulsePin, HIGH);
		}
		
		if (digitalRead(this->zHomingPin) == LOW)
		{
			digitalWrite(this->zPulsePin, HIGH);
		}
	
		if (digitalRead(this->xHomingPin) == LOW || digitalRead(this->yHomingPin) == LOW || digitalRead(this->zHomingPin) == LOW)
		{
			// If both X and Y-axis are called with digitalWrite() before a delay will make diagnonal movement possible, while also simultaneously handling the Z-axis.
			delayMicroseconds(400);		
			digitalWrite(this->xPulsePin, LOW);
			digitalWrite(this->yPulsePin, LOW);
			digitalWrite(this->zPulsePin, LOW);
			delayMicroseconds(400);
		}

		// If all homing pins are HIGH then we successfully managed to return back to the default position.
		if (digitalRead(this->xHomingPin) == HIGH && digitalRead(this->yHomingPin) == HIGH && digitalRead(this->zHomingPin) == HIGH)
		{
			this->SetXAxis(0);
			this->SetYAxis(0);
			this->SetYAxis(0);
			reachedEnd = true;
		}
	}
}

void RobotArm::HomeWithClaw()
{
	//REED6_HOMING_Y 37
	//REED7_HOMING_X 38
	//REED8_HOMING_Z 39
	//REED9_HOMING_CLAW

	// Conveyor belt positions:
	// x:3 y:0		x:3 y:1		x:3 y:2
	// x:2 y:0		x:2 y:1		x:2 y:2
	// x:1 y:0		x:1 y:1		x:1 y:2
	//
	// Grid row. Default position = x:0 y:0
	// x:0 y:0		x:0 y:1		x:0 y:2

	bool reachedEnd = false;

	// Set direction from the conveyor belt to the grid. From top to bottom, from right to left.
	digitalWrite(this->xDirectionPin, LOW);
	digitalWrite(this->yDirectionPin, LOW);
	digitalWrite(this->zDirectionPin, LOW);
	digitalWrite(this->claw.GetDirectionPin(), LOW);

	// Handle X, Y and Z-axis movement simultaneously with digitalWrite().
	while (!reachedEnd)
	{
		if (digitalRead(this->xHomingPin) == LOW)
		{
			digitalWrite(this->xPulsePin, HIGH);
		}
		
		if (digitalRead(this->yHomingPin) == LOW)
		{
			digitalWrite(this->yPulsePin, HIGH);
		}
		
		if (digitalRead(this->zHomingPin) == LOW)
		{
			digitalWrite(this->zPulsePin, HIGH);
		}
		
		if (digitalRead(this->claw.GetHomingPin()) == LOW)
		{
			digitalWrite(this->claw.GetPulsePin(), HIGH);
		}
		
		if (digitalRead(this->xHomingPin) == LOW || digitalRead(this->yHomingPin) == LOW || digitalRead(this->zHomingPin) == LOW || digitalRead(this->claw.GetHomingPin()) == LOW)
		{
			// If both X and Y-axis are called with digitalWrite() before a delay will make diagnonal movement possible, while also simultaneously handling the Z-axis and the claw.
			delayMicroseconds(400);
			digitalWrite(this->xPulsePin, LOW);
			digitalWrite(this->yPulsePin, LOW);
			digitalWrite(this->zPulsePin, LOW);
			digitalWrite(this->claw.GetPulsePin(), LOW);
			delayMicroseconds(400);
		}

		// If all homing pins are HIGH then we successfully managed to return back to the default position.
		if (digitalRead(this->xHomingPin) == HIGH && digitalRead(this->yHomingPin) == HIGH && digitalRead(this->zHomingPin) == HIGH && digitalRead(this->claw.GetHomingPin()) == HIGH)
		{
			this->SetXAxis(0);
			this->SetYAxis(0);
			this->SetYAxis(0);
			reachedEnd = true;
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
	return this->x;
}

void RobotArm::SetXAxis(int value)
{
	this->x = value;
}

int RobotArm::GetYAxis()
{
	return this->y;
}

void RobotArm::SetYAxis(int value)
{
	this->y = value;
}

int RobotArm::GetZAxis()
{
	return this->z;
}

void RobotArm::SetZAxis(int value)
{
	this->z = value;
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
	else if (y < minimumBoundary)
	{
		value = minimumBoundary;
	}
	
	return value;
}

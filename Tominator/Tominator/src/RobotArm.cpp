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
	this->Home();
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
	// Grid row. Default (home) position = x:0 y:0
	// x:0 y:0		x:0 y:1		x:0 y:2
	
	int stepsX = 0;
	int stepsY = 0;
	int stepsZ = 0;
	int differenceX = 0;
	int differenceY = 0;
	int differenceZ = 0;

	// Check robot arm boundaries.
	newX = CheckXAxisBoundary(newX);
	newY = CheckYAxisBoundary(newY);

	// Set the direction to go to either the grid or the conveyor belt.
	// X from bottom (x:0) to top (x:3), Y from left (y:0) to right (y:2), Z from up to down.	
	// If the current X, Y and Z-axis are less than the passed parameters then the robot needs to go into the opposite direction.
	if (this->GetXAxis() < newX)
	{
		digitalWrite(this->xDirectionPin, HIGH);
	}
	else
	{
		digitalWrite(this->xDirectionPin, LOW);		
	}
	
	if (this->GetYAxis() <= newY)
	{
		digitalWrite(this->yDirectionPin, LOW);
	}
	else
	{
		digitalWrite(this->yDirectionPin, HIGH);
	}

	if (this->GetZAxis() > newZ)
	{
		digitalWrite(this->zDirectionPin, LOW);
	}
	else
	{
		digitalWrite(this->zDirectionPin, HIGH);
	}
	
	// Calculate difference between new X, Y and Z-axis.
	differenceX = abs(newX - this->GetXAxis());
	differenceY = abs(newY - this->GetYAxis());
	differenceZ = abs(newZ - this->GetZAxis());

	// If current X-axis is 0 then the robot is already above the grid.
	if (this->GetXAxis() == this->minimumBoundary)
	{
		// If newX is 0, then this means the robot stays under the grid. Only the Y-axis steps should be calculated.
		if (differenceX == this->minimumBoundary)
		{
			stepsY = differenceY * motorStepsGridY;
			stepsZ = differenceZ * motorStepsGridZ;
		}
		else if (differenceX > this->minimumBoundary)
		{
			// If newX is greater then 0, then the robot needs to go to the conveyor belt. An offset should be added to stay under the right row and column.			
			if (differenceY > this->minimumBoundary)
			{
				stepsY = differenceY * motorStepsConveyorBelt;
			}
			
			if (newX > 1)
			{
				stepsX = differenceX * motorStepsConveyorBeltX + motorStepsConveyorXOffset;
			}
			else
			{
				stepsX = differenceX * motorStepsConveyorBelt + motorStepsConveyorXOffset;
			}
			
			if (!this->GetYAxis() > minimumBoundary)
			{
				stepsY += motorStepsColumnZeroOffset;
			}
		}
		
		stepsZ = differenceZ * motorStepsZ;
	}
	else if (this->GetXAxis() > this->minimumBoundary) // If current X-axis is greater than 0, then the robot is somewhere on the conveyor belt.
	{
		// If newX is greater than 0, then the robot moves to another X-axis on the conveyor belt
		if (differenceX > this->minimumBoundary)
		{
			stepsX = differenceX * motorStepsConveyorBelt;
			stepsY = differenceY * motorStepsConveyorBelt;
		}
		else if (differenceX == this->minimumBoundary)
		{
			// The robot goes back to the grid if newX is 0.
			stepsX = differenceX * motorStepsConveyorBelt + motorStepsConveyorXOffset;
			stepsY = differenceY * motorStepsGridY;
		}
		
		stepsZ = differenceZ * motorStepsZ;
	}
	
	if (this->GetZAxis() != newZ)
	{
		while (stepsZ > 0)
		{
			stepsZ--;
			digitalWrite(this->zPulsePin, HIGH);
			delayMicroseconds(delayZAxis);
			digitalWrite(this->zPulsePin, LOW);
			delayMicroseconds(delayZAxis);
		}
		
		this->SetZAxis(newZ);
	}
	
	if (this->GetXAxis() != newX)
	{
		while (stepsX > 0)
		{
			stepsX--;
			digitalWrite(this->xPulsePin, HIGH);
			delayMicroseconds(delay);
			digitalWrite(this->xPulsePin, LOW);
			delayMicroseconds(delay);
		}

		this->SetXAxis(newX);
	}

	if (this->GetYAxis() != newY || this->GetXAxis() > this->minimumBoundary)
	{
		while (stepsY > 0)
		{
			stepsY--;
			digitalWrite(this->yPulsePin, HIGH);
			delayMicroseconds(delay);
			digitalWrite(this->yPulsePin, LOW);
			delayMicroseconds(delay);
		}
		
		this->SetYAxis(newY);
	}
	
	if (differenceZ > this->minimumBoundary)
	{
		int offset = 1300;
		
		while (offset > 0 && newZ == 3)
		{
			offset--;
			digitalWrite(this->zPulsePin, HIGH);
			delayMicroseconds(delayZAxis);
			digitalWrite(this->zPulsePin, LOW);
			delayMicroseconds(delayZAxis);			
		}
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

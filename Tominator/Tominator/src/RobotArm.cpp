#include "RobotArm.h"
#include "TominatorPins.h"

RobotArm::RobotArm()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->minimumBoundary = 0;
	this->maximumXBoundary = 3;
	this->maximumYBoundary = 2;
}

RobotArm::RobotArm(int xPulsePin, int xDirectionPin, int yPulsePin, int yDirectionPin, int zPulsePin, int zDirectionPin, Claw claw) : RobotArm()
{
	this->xPulsePin = xPulsePin;
	this->xDirectionPin = xDirectionPin;
	this->yPulsePin = yPulsePin;
	this->yDirectionPin = yDirectionPin;
	this->zPulsePin = zPulsePin;
	this->zDirectionPin = zDirectionPin;
	this->claw = claw;

	pinMode(this->xPulsePin, OUTPUT);
	pinMode(this->xDirectionPin, OUTPUT);
	pinMode(this->yPulsePin, OUTPUT);
	pinMode(this->yDirectionPin, OUTPUT);
	pinMode(this->zPulsePin, OUTPUT);
	pinMode(this->zDirectionPin, OUTPUT);
}

RobotArm::RobotArm(int xPulsePin, int xDirectionPin, int yPulsePin, int yDirectionPin, int zPulsePin, int zDirectionPin, int clawPulsePin, int clawDirectionPin) : RobotArm()
{
	this->xPulsePin = xPulsePin;
	this->xDirectionPin = xDirectionPin;
	this->yPulsePin = yPulsePin;
	this->yDirectionPin = yDirectionPin;
	this->zPulsePin = zPulsePin;
	this->zDirectionPin = zDirectionPin;
	this->claw = Claw(clawPulsePin, clawDirectionPin);
	
	pinMode(this->xPulsePin, OUTPUT);
	pinMode(this->xDirectionPin, OUTPUT);
	pinMode(this->yPulsePin, OUTPUT);
	pinMode(this->yDirectionPin, OUTPUT);
	pinMode(this->zPulsePin, OUTPUT);
	pinMode(this->zDirectionPin, OUTPUT);
}

RobotArm::~RobotArm()
{
}

void RobotArm::HandleArm(int newX, int newY, int newZ)
{
	// Grid positions:
	// x:3 y:0		x:3 y:1		x:3 y:2
	// x:2 y:0		x:2 y:1		x:2 y:2
	// x:1 y:0		x:1 y:1		x:1 y:2
	//
	// Begin positions/row:
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
	// Making sure that both digitalWrite() for X and Y-axis are called before a delay allows for diagnonal movement.
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

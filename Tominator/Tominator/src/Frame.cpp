#include "Frame.h"
#include "TominatorPins.h"

Frame::Frame()
{
} 

Frame::Frame(DCMotor* dcMotor, UltrasonicSensor gridSideUltrasonicSensor, UltrasonicSensor sortingSideUltrasonicSensor, int reedGridSidePin, int reedSortingSidePin, Grid* grid, ConveyorBelt* conveyorBelt) : Frame()
{
	this->grid = grid;
	this->dcMotor = dcMotor;
	this->gridSideUltrasonicSensor = gridSideUltrasonicSensor;
	this->sortingSideUltrasonicSensor = sortingSideUltrasonicSensor;
	this->reedGridSidePin = reedGridSidePin;
	this->reedSortingSidePin = reedSortingSidePin;
	this->conveyorBelt = conveyorBelt;
	pinMode(reedGridSidePin, INPUT);
	pinMode(reedSortingSidePin, INPUT);
}

Frame::~Frame()
{
}

void Frame::HandleDCMotor(DirectionType direction)
{
	UltrasonicSensor ultrasonicSensor;
	int speedPercentage = 20;
	int percentageIncrement = 2;
	long duration = 0;
	int distance = 0;
	bool nearingEnd = false;
	bool reachedEnd = false;
	
	this->GetDCMotor()->Start(direction);
	
	if (direction == DirectionType::Forward)
	{
		ultrasonicSensor = this->gridSideUltrasonicSensor;
	}
	else
	{
		ultrasonicSensor = this->sortingSideUltrasonicSensor;	
	}
	
	while(!reachedEnd)
	{
		speedPercentage += percentageIncrement;
		this->GetDCMotor()->SetSpeedInPercentage(speedPercentage);
		this->GetDCMotor()->Run();
		
		duration = ultrasonicSensor.GetDuration();	
		distance = duration / 2 / 29.1;
		
		if (distance <= 135)
		{
			this->GetDCMotor()->Stop();
			reachedEnd = true;
		}
	}
}

void Frame::HandleDCMotorOffset(bool isAtGridSide)
{
	int iterations = 5;
	UltrasonicSensor ultrasonicSensor;
	long duration = 0;
	int distance = 0;
	int offset = 0;
	int minRange = 0;
	int maxRange = 0;
	DirectionType forward = DirectionType::Reverse;
	DirectionType reverse = DirectionType::Forward;

	if (isAtGridSide)
	{
		BaseGridState* state = this->grid->GetState();
		ultrasonicSensor = this->gridSideUltrasonicSensor;
		forward = DirectionType::Forward;
		reverse = DirectionType::Reverse;
		
		switch (state->GetStateTypes()[state->ToString()])
		{
			case BaseGridStateType::FirstRowEmptyStateType:
				offset = 130;
				break;
			case BaseGridStateType::SecondRowEmptyStateType:
				offset = 160;
				break;
			case BaseGridStateType::BaseGridType:
			case BaseGridStateType::NoneRowEmptyStateType:
			case BaseGridStateType::ThirdRowEmptyStateType:
			default:
				break;
		}
	}
	else
	{	
		BaseGridState* state = this->conveyorBelt->GetState();
		ultrasonicSensor = this->sortingSideUltrasonicSensor;
		forward = DirectionType::Reverse;
		reverse = DirectionType::Forward;
		
		switch (state->GetStateTypes()[state->ToString()])
		{
			case BaseGridStateType::FirstRowEmptyStateType:
				offset = 108;
				break;
			case BaseGridStateType::SecondRowEmptyStateType:
				offset = 82;
				break;
			case BaseGridStateType::BaseGridType:
			case BaseGridStateType::NoneRowEmptyStateType:
			case BaseGridStateType::ThirdRowEmptyStateType:
			default:
				offset = 0;
				break;
		}
	}
	
	minRange = offset - 2;
	maxRange = offset + 2;
	
	this->GetDCMotor()->Start(DirectionType::Reverse);
	this->GetDCMotor()->SetSpeedInPercentage(100);
	
	while(true)
	{
		if (isAtGridSide)
		{
			distance = ultrasonicSensor.GetDuration() / 2 / 29.1;
		}
		else
		{
			distance = 0;
						
			for (int i = 0; i < iterations; i++)
			{
				distance += ultrasonicSensor.GetDuration() / 2 / 29.1;
			}
						
			distance /= iterations;
		}
			
		if (distance > maxRange)
		{
			this->GetDCMotor()->Start(forward);
		}
		else if (distance < minRange)
		{
			this->GetDCMotor()->Start(reverse);
		}
		else if (distance > minRange && distance < maxRange)
		{
			break;
		}
			
		this->GetDCMotor()->Run();
	}
	
	this->GetDCMotor()->Stop();
}

DCMotor* Frame::GetDCMotor()
{
	return this->dcMotor;
}

void Frame::Home()
{
	this->GetDCMotor()->Start(DirectionType::Forward);
	this->GetDCMotor()->SetSpeedInPercentage(50);
	
	while (true)
	{
		// If the homing pin is HIGH then we successfully managed to return back to the default position.
		if (digitalRead(this->reedGridSidePin) == LOW)
		{
			break;
		}
		else if (digitalRead(this->reedGridSidePin))
		{
			this->GetDCMotor()->Run();
		}
	}
	
	this->GetDCMotor()->Stop();
}

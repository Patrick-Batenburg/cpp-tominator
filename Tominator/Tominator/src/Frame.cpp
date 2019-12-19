#include "Frame.h"
#include "TominatorPins.h"

Frame::Frame()
{
} 

Frame::Frame(DCMotor dcMotor, UltrasonicSensor gridSideUltrasonicSensor, UltrasonicSensor sortingSideUltrasonicSensor, int reedGridSidePin, int reedSortingSidePin, Grid* grid, ConveyorBelt* conveyorBelt) : Frame()
{
	this->dcMotor = dcMotor;
	this->gridSideUltrasonicSensor = gridSideUltrasonicSensor;
	this->sortingSideUltrasonicSensor = sortingSideUltrasonicSensor;
	this->reedGridSidePin = reedGridSidePin;
	this->reedSortingSidePin = reedSortingSidePin;
	this->grid = grid;
	this->conveyorBelt = conveyorBelt;
	pinMode(reedGridSidePin, INPUT);
	pinMode(reedSortingSidePin, INPUT);
}

Frame::~Frame()
{
}

void Frame::HandleDCMotor(DirectionType direction)
{
	int speedPercentage = 20;
	int percentageIncrement = 2;
	long duration = 0;
	int distance = 0;
	bool nearingEnd = false;
	bool reachedEnd = false;
	
	this->GetDCMotor().Start(direction);
	
	digitalWrite(this->gridSideUltrasonicSensor.GetTriggerPin(), LOW);
	digitalWrite(this->sortingSideUltrasonicSensor.GetTriggerPin(), LOW);

	delayMicroseconds(2);
	
	while(!reachedEnd)
	{
		speedPercentage += percentageIncrement;
		this->GetDCMotor().SetSpeedInPercentage(speedPercentage);
		this->GetDCMotor().Run();
		
		// DirectionType::Forward = true, go to sorting side.
		// DirectionType::Reverse = false, go to grid side.
		if (direction)
		{
			digitalWrite(this->sortingSideUltrasonicSensor.GetTriggerPin(), HIGH);
			delayMicroseconds(10);
			digitalWrite(this->sortingSideUltrasonicSensor.GetTriggerPin(), LOW);
			duration = pulseIn(this->sortingSideUltrasonicSensor.GetEchoPin(), HIGH);
		}
		else
		{
			digitalWrite(this->gridSideUltrasonicSensor.GetTriggerPin(), HIGH);
			delayMicroseconds(10);
			digitalWrite(this->gridSideUltrasonicSensor.GetTriggerPin(), LOW);
			duration = pulseIn(this->gridSideUltrasonicSensor.GetEchoPin(), HIGH);
		}
		
		distance = duration * 0.034 / 2;
		
		if (distance <= 30)
		{
			this->GetDCMotor().SmoothStop(duration);
		}
		
		if (digitalRead(this->reedGridSidePin) == HIGH || digitalRead(this->reedSortingSidePin) == HIGH)
		{
			bool isAtGridSide = false;
			
			if (digitalRead(this->reedGridSidePin) == HIGH)
			{
				isAtGridSide = true;
			}
			
			reachedEnd = true;
			this->GetDCMotor().Stop();		
			this->HandleDCMotorOffset(direction);
		}
	}
}

void Frame::HandleDCMotorOffset(DirectionType direction)
{
	int speed = 50;
	int distance = 0;
	int offset = 0;
	DirectionType oldDirection = direction;
	
	// Inverse direction.
	if (direction == DirectionType::Forward)
	{
		direction = DirectionType::Reverse;
	}
	else
	{
		direction = DirectionType::Forward;	
	}
	
	// DirectionType::Forward = true, is at sorting side.
	if (oldDirection == DirectionType::Forward)
	{
		switch (this->conveyorBelt->GetState()->GetStateTypes()[this->conveyorBelt->GetState()->ToString()])
		{
			case BaseGridStateType::FirstRowEmptyStateType:
				offset = 1;
				break;
			case BaseGridStateType::SecondRowEmptyStateType:
				offset = 2;
				break;
			case BaseGridStateType::BaseGridType:
			case BaseGridStateType::NoneRowEmptyStateType:
			case BaseGridStateType::ThirdRowEmptyStateType:
			default:
				offset = 0;
				break;
		}
	}
	else // DirectionType::Reverse = false, is at grid side.
	{	
		switch (this->grid->GetState()->GetStateTypes()[this->grid->GetState()->ToString()])
		{
			case BaseGridStateType::FirstRowEmptyStateType:
				offset = 1;
				break;
			case BaseGridStateType::SecondRowEmptyStateType:
				offset = 2;
				break;
			case BaseGridStateType::BaseGridType:
			case BaseGridStateType::NoneRowEmptyStateType:
			case BaseGridStateType::ThirdRowEmptyStateType:
			default:
				offset = 0;
				break;
		}
	}
	
	distance = offset * speed;
	this->GetDCMotor().Start(direction);
	
	while(distance > 0)
	{
		distance--;
		this->GetDCMotor().Run();
	}
}

DCMotor Frame::GetDCMotor()
{
	return this->dcMotor;
}

//void Frame::HandleFrame(DirectionType direction)
//{
	//int speed = 50;
	//int speedIncrement = 5;
	//int speedOffset = 40;
	//long duration = 0;
	//int distance = 0;
	//bool nearingEnd = false;
	//bool reachedEnd = false;
	//
	//this->GetDCMotor().Start(direction);
	//
	//digitalWrite(this->gridSideUltrasonicSensor.GetTriggerPin(), LOW);
	//digitalWrite(this->sortingSideUltrasonicSensor.GetTriggerPin(), LOW);
//
	//delayMicroseconds(2);
	//
	//while(!reachedEnd)
	//{
		//speed += speedIncrement;
		//this->GetDCMotor().SetSpeed(speed);
		//this->GetDCMotor().Run();
		//
		//// DirectionType::Forward = true, go to sorting side.
		//// DirectionType::Reverse = false, go to grid side.
		//if (direction)
		//{
			//digitalWrite(this->sortingSideUltrasonicSensor.GetTriggerPin(), HIGH);
			//delayMicroseconds(10);
			//digitalWrite(this->sortingSideUltrasonicSensor.GetTriggerPin(), LOW);
			//duration = pulseIn(this->sortingSideUltrasonicSensor.GetEchoPin(), HIGH);
		//}
		//else
		//{
			//digitalWrite(this->gridSideUltrasonicSensor.GetTriggerPin(), HIGH);
			//delayMicroseconds(10);
			//digitalWrite(this->gridSideUltrasonicSensor.GetTriggerPin(), LOW);
			//duration = pulseIn(this->gridSideUltrasonicSensor.GetEchoPin(), HIGH);
		//}
		//
		//distance = duration * 0.034 / 2;
		//
		//if (distance <= 30 && distance > 15)
		//{
			//speedIncrement = speed / speedOffset * -1;
		//}
		//else if (distance <= 15 && nearingEnd == false)
		//{
			//speedIncrement = speed / speedOffset * -1;
			//nearingEnd = true;
		//}
		//
		//if (digitalRead(this->reedGridSidePin) == HIGH || digitalRead(this->reedSortingSidePin) == HIGH)
		//{
			//bool isAtGridSide = false;
			//
			//if (digitalRead(this->reedGridSidePin) == HIGH)
			//{
				//isAtGridSide = true;
			//}
			//
			//reachedEnd = true;
			//this->GetDCMotor().Stop();
			//
			//if (direction == DirectionType::Forward)
			//{
				//this->HandleFrameOffset(isAtGridSide, DirectionType::Reverse);
			//}
			//else
			//{
				//this->HandleFrameOffset(isAtGridSide, DirectionType::Forward);
			//}
		//}
	//}
//}

#include "ConveyorBelt.h"
#include "TominatorPins.h"

ConveyorBelt::ConveyorBelt() : BaseGrid()
{
	this->transportedWaterBalloons = 0;
	this->transportedWaterBalloonsGoal = 9;
	this->reedPin = 0;
	this->firstRowType = WaterBalloonType::Empty;
	this->secondRowType = WaterBalloonType::Empty;
	this->thirdRowType = WaterBalloonType::Empty;
}

ConveyorBelt::ConveyorBelt(DCMotor* dcMotor, int reedPin) : ConveyorBelt()
{
	this->dcMotor = dcMotor;
	this->reedPin = reedPin;
}

ConveyorBelt::~ConveyorBelt()
{
}

bool ConveyorBelt::CanAddWaterBalloon(WaterBalloon waterBalloon)
{
	bool suceeded = false;

	// Water balloons always get added from left to right.
	// If the very first cell of a row is either empty or the same type as the water balloon, then update the corresponding row type variable.
	// If there was only checked whenever the first was only empty, then this may lead to all 3 row type variables becoming the same type other than empty.
	// Essentially, assigning duplicate types to a row type variable is what we want to avoid here.
	if (this->waterBalloonPositions[0][0].GetType() == WaterBalloonType::Empty || this->waterBalloonPositions[0][0].GetType() == waterBalloon.GetType())
	{
		this->firstRowType = waterBalloon.GetType();
	}
	else if (this->waterBalloonPositions[1][0].GetType() == WaterBalloonType::Empty || this->waterBalloonPositions[1][0].GetType() == waterBalloon.GetType())
	{
		this->secondRowType = waterBalloon.GetType();
	}
	else if (this->waterBalloonPositions[2][0].GetType() == WaterBalloonType::Empty || this->waterBalloonPositions[2][0].GetType() == waterBalloon.GetType())
	{
		this->thirdRowType = waterBalloon.GetType();
	}

	// If the water balloon type matches any of the 3 row type variables, set the corresponding row. 
	// We then loop through that row to see if there space to place a new water balloon. This is indicated by a WaterBalloonType::Empty in the 2D matrix.
	// If this succeeds, then we return true and set the column. If it fails somehow, for example all rows appeared to be filled, then we return false.
	if (waterBalloon.GetType() == this->GetFirstRowType())
	{
		this->SetCurrentRow(0);

		for (int i = 0; i < this->waterBalloonPositions[this->GetCurrentRow()].size(); i++)
		{
			if (this->waterBalloonPositions[this->GetCurrentRow()][i].GetType() == WaterBalloonType::Empty)
			{
				suceeded = true;
				this->SetCurrentColumn(i);
				break;
			}
		}
	}
	else if (waterBalloon.GetType() == this->GetSecondRowType())
	{
		this->SetCurrentRow(1);

		for (int i = 0; i < this->waterBalloonPositions[this->GetCurrentRow()].size(); i++)
		{
			if (this->waterBalloonPositions[this->GetCurrentRow()][i].GetType() == WaterBalloonType::Empty)
			{
				suceeded = true;
				this->SetCurrentColumn(i);
				break;
			}
		}
	}
	else if (waterBalloon.GetType() == this->GetThirdRowType())
	{
		this->SetCurrentRow(2);

		for (int i = 0; i < this->waterBalloonPositions[this->GetCurrentRow()].size(); i++)
		{
			if (this->waterBalloonPositions[this->GetCurrentRow()][i].GetType() == WaterBalloonType::Empty)
			{
				suceeded = true;
				this->SetCurrentColumn(i);
				break;
			}
		}
	}

	return suceeded;
}

void ConveyorBelt::AddWaterBalloon(WaterBalloon waterBalloon)
{
	this->waterBalloonPositions[this->GetCurrentRow()][this->GetCurrentColumn()] = waterBalloon;
	this->IncrementTransportedWaterBalloons();
}

void ConveyorBelt::HandleDCMotor()
{
	if (this->GetTransportedWaterBalloons() == this->GetTransportedWaterBalloonsGoal())
	{
		while (digitalRead(this->reedPin) == LOW)
		{
			this->dcMotor->Run();
		}	
	}
}

WaterBalloonType ConveyorBelt::GetFirstRowType()
{
	return this->firstRowType;
}

void ConveyorBelt::SetFirstRowType(WaterBalloonType value)
{
	this->firstRowType = value;
}

WaterBalloonType ConveyorBelt::GetSecondRowType()
{
	return this->secondRowType;
}

void ConveyorBelt::SetSecondRowType(WaterBalloonType value)
{
	this->secondRowType = value;
}

enum WaterBalloonType ConveyorBelt::GetThirdRowType()
{
	return this->thirdRowType;
}

void ConveyorBelt::SetThirdRowType(WaterBalloonType value)
{
	this->thirdRowType = value;
}

int ConveyorBelt::GetTransportedWaterBalloons()
{
	return this->transportedWaterBalloons;
}

int ConveyorBelt::GetTransportedWaterBalloonsGoal()
{
	return this->transportedWaterBalloonsGoal;
}

void ConveyorBelt::SetTransportedWaterBalloonsGoal(int value)
{
	this->transportedWaterBalloonsGoal = value;
}

void ConveyorBelt::SetState(BaseGridState* value)
{
	if (this->GetTransportedWaterBalloons() == this->GetTransportedWaterBalloonsGoal())
	{
		this->state = value;
	}
}

DCMotor* ConveyorBelt::GetDCMotor()
{
	return this->dcMotor;
}

void ConveyorBelt::SetTransportedWaterBalloons(int value)
{
	this->transportedWaterBalloons = value;
}

void ConveyorBelt::IncrementTransportedWaterBalloons()
{
	this->transportedWaterBalloons++;
}

void ConveyorBelt::Sort()
{
	int counter = 0;
	bool isUnderSensor = false;
	this->GetDCMotor()->Start(DirectionType::Reverse);
	this->GetDCMotor()->SetSpeedInPercentage(100);

	if (digitalRead(this->reedPin))
	{
		isUnderSensor = true;
	}
	
	while (isUnderSensor)
	{
		counter++;
		this->GetDCMotor()->Run();

		// Amount of motor steps needed to get a sufficient distance away from the reed pin.
		if (digitalRead(this->reedPin) == LOW && counter > motorSteps)
		{
			isUnderSensor = false;
		}
	}
	
	while (true)
	{
		if (digitalRead(this->reedPin))
		{
			break;
		}
		else if (digitalRead(this->reedPin) == LOW)
		{
			this->GetDCMotor()->Run();
		}
	}
	
	this->GetDCMotor()->Stop();
	
	Serial.print("Flag: ");
	Serial.println(counter);	
}

void ConveyorBelt::Home()
{
	this->GetDCMotor()->Start(DirectionType::Reverse);
	this->GetDCMotor()->SetSpeedInPercentage(100);
	
	while (true)
	{
		// If the homing pin is HIGH then we successfully managed to return back to the default position.
		if (digitalRead(this->reedPin))
		{
			break;
		}
		else if (digitalRead(this->reedPin) == LOW)
		{
			this->GetDCMotor()->Run();
		}
	}
	
	this->GetDCMotor()->Stop();
}

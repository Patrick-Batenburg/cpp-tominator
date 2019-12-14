#include "ConveyorBelt.h"
#include "TominatorPins.h"

ConveyorBelt::ConveyorBelt() : BaseGrid()
{
	this->transportedWaterBalloons = 0;
	this->transportedWaterBalloonsGoal = 9;
	this->firstRowType = WaterBalloonType::Empty;
	this->secondRowType = WaterBalloonType::Empty;
	this->thirdRowType = WaterBalloonType::Empty;
}

ConveyorBelt::ConveyorBelt(DCMotor dcMotor) : ConveyorBelt()
{
	this->dcMotor = dcMotor;
}

ConveyorBelt::~ConveyorBelt()
{
}

bool ConveyorBelt::CanAddWaterBalloon(WaterBalloon waterBalloon)
{
	bool suceeded = false;

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
			else
			{
				suceeded = false;
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
			else
			{
				suceeded = false;
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
		this->dcMotor.Run();
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

DCMotor ConveyorBelt::GetDCMotor()
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

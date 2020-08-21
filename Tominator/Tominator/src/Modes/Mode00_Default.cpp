#include "Mode00_Default.h"
#include "Machine.h"

DefaultMode::DefaultMode()
{
}

DefaultMode::~DefaultMode()
{
}

void DefaultMode::Initialize(Machine* machine)
{
	machine->Home(2); // Home carriage
	machine->Home(5); // Homes to default position. x:0, y:0
}

void DefaultMode::HandlePlaceholder(Machine* machine)
{
	bool conveyorBeltIsAtColumnThree = false;
	bool gridIsAtColumnThree = false;
	bool skipOffsetY = false;
	int columnThreeOffset = 100;
	int zAxisMiddleOffset = 5000;
	int zAxisPlaceWaterBalloonOffset = 3000;
		
	for (int i = 0; i < 3; i++)
	{		
		for (int j = 0; j < 3; j++)
		{		
			if (i == 0 && j == 0)
			{
				machine->GetRobotArm().HandleZAxis(2);
			}
			else
			{
				machine->GetRobotArm().HandleZAxis(2, zAxisMiddleOffset, 0);
			}
			
			machine->CloseClaw();
			conveyorBeltIsAtColumnThree = machine->GetConveyorBelt()->GetCurrentColumn() == 2;		
			machine->GetRobotArm().HandleZAxis(1, zAxisMiddleOffset, 0);
			machine->WeighWaterBalloon();
			machine->GetControlPanel().Print("X: " + String(machine->GetGrid()->GetCurrentRow()), "Y: " + String(machine->GetGrid()->GetCurrentColumn()));

			if (gridIsAtColumnThree)
			{
				machine->GetRobotArm().HandleYAxisOffset(DirectionType::Reverse, columnThreeOffset);
			}	

			if (!skipOffsetY)
			{
				skipOffsetY = true;
				machine->GetRobotArm().HandleYAxisOffset(DirectionType::Forward);
			}
			
			machine->GetRobotArm().HandleXAxis(3 - machine->GetConveyorBelt()->GetCurrentRow());
			machine->GetRobotArm().HandleYAxis(machine->GetConveyorBelt()->GetCurrentColumn());
			
			machine->GetRobotArm().HandleZAxisOffset(zAxisPlaceWaterBalloonOffset, HIGH);
			machine->OpenClaw();
			machine->GetRobotArm().HandleZAxisOffset(zAxisPlaceWaterBalloonOffset, LOW);
			machine->GetRobotArm().HomeXAxis();
			
			if (machine->GetGrid()->GetCurrentColumn() == 2)
			{
				machine->GetRobotArm().HandleYAxisOffset(DirectionType::Forward, columnThreeOffset);
			}
			
			if (gridIsAtColumnThree)
			{
				skipOffsetY = false;
				machine->GetRobotArm().HomeYAxis();
			}
			else
			{
				machine->GetRobotArm().HandleYAxis(machine->GetGrid()->GetCurrentColumn());
			}
			
			gridIsAtColumnThree = machine->GetGrid()->GetCurrentColumn() == 2;
		}
		
		if (i < 2)
		{
			machine->GetGrid()->GetState()->Next(machine->GetGrid());
			machine->GetFrame().HandleDCMotorOffset(true);
		}	
	}
	
	machine->HandleFrame(DirectionType::Reverse);
	
	for (int i = 0; i < 3; i++)
	{
		machine->SortWaterBalloons();		
	}
}

String DefaultMode::ToString()
{
	return MODE0;
}

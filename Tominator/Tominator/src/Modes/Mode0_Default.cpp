#include "Mode0_Default.h"
#include "Machine.h"

DefaultMode::DefaultMode()
{
}

DefaultMode::~DefaultMode()
{
}

void DefaultMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(4);
	
	for (int i = 0; i < 2; i++)
	{
		//machine->HandleRobotArm(0, 0, 0);	// Make arm go down in the Z-axis.
		machine->HandleRobotArm(0, 0, 0);	// Make arm go down in the Z-axis.
		machine->CloseClaw();				// Grab water balloon.
		machine->WeighWaterBalloon();
		//machine->HandleRobotArm(0, 0, 3);	// Make arm go down in the Z-axis.
		machine->HandleRobotArm(abs(machine->GetConveyorBelt()->GetCurrentRow() -3), abs(machine->GetConveyorBelt()->GetCurrentColumn()-2), 0);	// Make arm go down in the Z-axis.
		machine->OpenClaw();				// Let go of water balloon.
		machine->Home(4);
	}
		
	//if (DEBUG)
	//{
		//for (int i = 0; i < machine->GetGrid()->GetWaterBalloonPositions().size(); i++)
		//{
			//for (int j = 0; j < machine->GetGrid()->GetWaterBalloonPositions()[i].size(); j++)
			//{
				//WaterBalloon waterBalloon = WaterBalloon(machine->GetGrid()->GetWaterBalloonPositions()[i][j].GetWeight());
				//machine->SetCurrentWaterBalloon(waterBalloon);
				//machine->WeighWaterBalloon();
			//}
		//}
		//
	//}
	//else
	//{
		//for (int i = 0; i < machine->GetGrid()->GetWaterBalloonPositions().size(); i++)
		//{
			//for (int j = 0; j < machine->GetGrid()->GetWaterBalloonPositions()[i].size(); j++)
			//{
				//machine->HandleRobotArm(machine->GetGrid()->GetCurrentRow(), machine->GetGrid()->GetCurrentColumn(), 0); // Go to grid.
				//machine->CloseClaw();					// Grab water balloon.
				//machine->WeighWaterBalloon();
				//machine->HandleRobotArm(0, 0, 0);		// Go to conveyor belt.
				//machine->OpenClaw();					// Let go of water balloon.
//
				//if (machine->GetConveyorBelt()->GetTransportedWaterBalloons() == machine->GetConveyorBelt()->GetTransportedWaterBalloonsGoal())
				//{
					//machine->SortWaterBalloons();
				//}
			//}
		//}
	//}
}

String DefaultMode::ToString()
{
	return MODE0;
}

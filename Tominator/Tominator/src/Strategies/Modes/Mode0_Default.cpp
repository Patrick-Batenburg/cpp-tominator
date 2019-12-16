#include "Mode0_Default.h"
#include "Machine.h"

using namespace std;

DefaultMode::DefaultMode()
{
}

DefaultMode::~DefaultMode()
{
}

void DefaultMode::HandlePlaceholder(Machine* machine)
{
	for (int i = 0; i < machine->GetGrid().GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine->GetGrid().GetWaterBalloonPositions()[i].size(); j++)
		{
			WaterBalloon waterBalloon = WaterBalloon(machine->GetGrid().GetWaterBalloonPositions()[i][j].GetWeight());
			//std::cout << to_string(waterBalloon.GetWeight()) << " ";
			machine->HandleRobotArm(machine->GetGrid().GetCurrentRow(), machine->GetGrid().GetCurrentColumn(), 0); // Go to grid.
			machine->CloseClaw();					// Grab water balloon.
			machine->SetCurrentWaterBalloon(waterBalloon);
			machine->WeighWaterBalloon();
			machine->HandleRobotArm(0, 0, 0);		// Go to conveyor belt.
			machine->OpenClaw();					// Let go of water balloon.

			if (machine->GetConveyorBelt().GetTransportedWaterBalloons() == machine->GetConveyorBelt().GetTransportedWaterBalloonsGoal())
			{
				machine->SortWaterBalloons();
			}
		}
	}
}

string DefaultMode::ToString()
{
	return MODE0;
}

#include "Mode5_Sorting.h"
#include "Machine.h"

using namespace std;

SortingMode::SortingMode()
{
}

SortingMode::~SortingMode()
{
}

void SortingMode::HandlePlaceholder(Machine* machine)
{
	// Grab a water balloon from the grid, weigh it and place onto the conveyor belt. Repeat this process 3x after which 1 row should be filled and can be sorted.
	machine->GetConveyorBelt().SetTransportedWaterBalloonsGoal(3); // Need only 3 water balloon instead of the default 9.
	
	machine->HandleArm(0, 0, 0);
	machine->CloseClaw();
	machine->WeighWaterBalloon();
	machine->OpenClaw();

	machine->HandleArm(0, 0, 0);
	machine->CloseClaw();
	machine->WeighWaterBalloon();
	machine->OpenClaw();

	machine->HandleArm(0, 0, 0);
	machine->CloseClaw();
	machine->WeighWaterBalloon();
	machine->OpenClaw();

	machine->SortWaterBalloons();
}

string SortingMode::ToString()
{
	return MODE5;
}

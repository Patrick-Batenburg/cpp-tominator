#include "Mode5_Sorting.h"
#include "Machine.h"

SortingMode::SortingMode()
{
}

SortingMode::~SortingMode()
{
}

void SortingMode::HandlePlaceholder(Machine* machine)
{
	// Grab a water balloon from the grid, weigh it and place onto the conveyor belt. Repeat this process 3x after which 1 row should be filled and can be sorted.
	
	Cell nearestCell = machine->GetConveyorBelt().GetNearestUnusedCell(); // Helper method to get the next position, but is very time consuming due to reiterating over a 2D matrix every time it is called.
	machine->GetConveyorBelt().SetTransportedWaterBalloonsGoal(3); // Need only 3 water balloons instead of the default 9.

	machine->HomingRobotArm();																				// Homes to default position. x:0, y:0
	
	machine->HandleRobotArm(machine->GetGrid().GetCurrentRow(), machine->GetGrid().GetCurrentColumn(), 3);	// Go to 1st water balloon
	machine->CloseClaw();																					// Grab the 1st water balloon
	machine->WeighWaterBalloon();
	
	machine->HandleRobotArm(3, nearestCell.Column, 0);														// Go to conveyor belt. positions: x:3, y:0
	machine->OpenClaw();																					// Release water balloon

	machine->HandleRobotArm(machine->GetGrid().GetCurrentRow(), machine->GetGrid().GetCurrentColumn(), 3);	// Go to grid positions: x:0, y:1
	machine->CloseClaw();
	machine->WeighWaterBalloon();
	nearestCell = machine->GetConveyorBelt().GetNearestUnusedCell();
	machine->HandleRobotArm(3, nearestCell.Column, 0);														// Go to conveyor belt. positions: x:3, y:1
	machine->OpenClaw();

	machine->HandleRobotArm(machine->GetGrid().GetCurrentRow(), machine->GetGrid().GetCurrentColumn(), 3);	// Go to grid positions: x:0, y:2
	machine->CloseClaw();
	machine->WeighWaterBalloon();
	nearestCell = machine->GetConveyorBelt().GetNearestUnusedCell();
	machine->HandleRobotArm(3, nearestCell.Column, 0);														// Go to conveyor belt. positions: x:3, y:2
	machine->OpenClaw();

	machine->SortWaterBalloons();
}

String SortingMode::ToString()
{
	return MODE5;
}

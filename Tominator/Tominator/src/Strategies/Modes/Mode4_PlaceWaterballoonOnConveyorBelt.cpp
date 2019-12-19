#include "Mode4_PlaceWaterballoonOnConveyorBelt.h"
#include "Machine.h"

PlaceWaterballoonOnConveyorBeltMode::PlaceWaterballoonOnConveyorBeltMode()
{
}

PlaceWaterballoonOnConveyorBeltMode::~PlaceWaterballoonOnConveyorBeltMode()
{
}

void PlaceWaterballoonOnConveyorBeltMode::HandlePlaceholder(Machine* machine)
{
	machine->CloseClaw();				// Grab water balloon.
	machine->WeighWaterBalloon();
	machine->HandleRobotArm(0, 0, 0);	// Go to conveyor belt.
	machine->OpenClaw();				// Let go of water balloon.
}

String PlaceWaterballoonOnConveyorBeltMode::ToString()
{
	return MODE4;
}

#include "Mode04_PlaceWaterballoonOnConveyorBelt.h"
#include "Machine.h"

PlaceWaterballoonOnConveyorBeltMode::PlaceWaterballoonOnConveyorBeltMode()
{
}

PlaceWaterballoonOnConveyorBeltMode::~PlaceWaterballoonOnConveyorBeltMode()
{
}

void PlaceWaterballoonOnConveyorBeltMode::Initialize(Machine* machine)
{
	machine->Home(4);
}

void PlaceWaterballoonOnConveyorBeltMode::HandlePlaceholder(Machine* machine)
{
	machine->HandleRobotArm(0, 0, 3);	// Make arm go down in the Z-axis.
	machine->CloseClaw();				// Grab water balloon.
	machine->WeighWaterBalloon();
	machine->HandleRobotArm(3, 2, 3);	// Make arm go down in the Z-axis.
	machine->OpenClaw();				// Let go of water balloon.
}

String PlaceWaterballoonOnConveyorBeltMode::ToString()
{
	return MODE4;
}

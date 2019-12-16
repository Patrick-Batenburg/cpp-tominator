#include "Mode4_PlaceWaterballoonOnConveyorBelt.h"
#include "Machine.h"

using namespace std;

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

string PlaceWaterballoonOnConveyorBeltMode::ToString()
{
	return MODE4;
}

#include "Mode3_GrabWaterBalloon.h"
#include "Machine.h"

GrabWaterBalloonMode::GrabWaterBalloonMode()
{
}

GrabWaterBalloonMode::~GrabWaterBalloonMode()
{
}

void GrabWaterBalloonMode::HandlePlaceholder(Machine* machine)
{
	machine->HandleRobotArm(0, 0, 3);	// Go to grid.
	machine->CloseClaw();				// Grab water balloon.
}

String GrabWaterBalloonMode::ToString()
{
	return MODE3;
}

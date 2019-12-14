#include "Mode3_GrabWaterBalloon.h"
#include "Machine.h"

using namespace std;

GrabWaterBalloonMode::GrabWaterBalloonMode()
{
}

GrabWaterBalloonMode::~GrabWaterBalloonMode()
{
}

void GrabWaterBalloonMode::HandlePlaceholder(Machine* machine)
{
	machine->HandleArm(0, 0, 0);	// Go to grid.
	machine->CloseClaw();			// Grab water balloon.
}

string GrabWaterBalloonMode::ToString()
{
	return MODE3;
}

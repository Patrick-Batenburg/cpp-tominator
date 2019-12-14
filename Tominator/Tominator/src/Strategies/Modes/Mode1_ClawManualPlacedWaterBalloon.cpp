#include "Mode1_ClawManualPlacedWaterBalloon.h"
#include "Machine.h"

using namespace std;

ClawManualPlacedWaterBalloonMode::ClawManualPlacedWaterBalloonMode()
{
}

ClawManualPlacedWaterBalloonMode::~ClawManualPlacedWaterBalloonMode()
{
}

void ClawManualPlacedWaterBalloonMode::HandlePlaceholder(Machine* machine)
{
	machine->OpenClaw();
	machine->CloseClaw();			// Place water balloon manually in the claw and close it.
	machine->WeighWaterBalloon();
	machine->HandleArm(0, 0, 0);	// Go to conveyor belt.
	machine->OpenClaw();			// Let go of water balloon.

	//machine->SortWaterBalloons();
}

string ClawManualPlacedWaterBalloonMode::ToString()
{
	return MODE1;
}
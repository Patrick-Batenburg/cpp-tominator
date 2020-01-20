#include "Mode1_ClawManualPlacedWaterBalloon.h"
#include "Machine.h"

ClawManualPlacedWaterBalloonMode::ClawManualPlacedWaterBalloonMode()
{
}

ClawManualPlacedWaterBalloonMode::~ClawManualPlacedWaterBalloonMode()
{
}

void ClawManualPlacedWaterBalloonMode::HandlePlaceholder(Machine* machine)
{
	machine->OpenClaw();
	machine->CloseClaw();				// Place water balloon manually in the claw and close it.
	machine->WeighWaterBalloon();
	machine->OpenClaw();				// Let go of water balloon.
	machine->GetControlPanel().Print("Weight: " + String(machine->GetCurrentWaterBalloon().GetWeight()), "Finished");
}

String ClawManualPlacedWaterBalloonMode::ToString()
{
	return MODE1;
}
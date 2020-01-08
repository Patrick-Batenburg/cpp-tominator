#include "Mode2_Quickness.h"
#include "Machine.h"

QuicknessMode::QuicknessMode()
{
}

QuicknessMode::~QuicknessMode()
{
}

void QuicknessMode::HandlePlaceholder(Machine* machine)
{
	machine->HandleRobotArm(0, 0, 0);	// Go to grid.
	machine->CloseClaw();				// Grab water balloon 1.
	machine->OpenClaw();				// Let go of water balloon 1.

	machine->HandleRobotArm(0, 1, 0);	// Go to next water balloon.
	machine->CloseClaw();				// Grab water balloon 2.
	machine->OpenClaw();				// Let go of water balloon 2.

	machine->HandleRobotArm(0, 2, 0);	// Go to water balloon.
	machine->CloseClaw();				// Grab water balloon 3.
	machine->OpenClaw();				// Let go of water balloon 3.
}

String QuicknessMode::ToString()
{
	return MODE2;
}
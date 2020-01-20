#include "Mode10_ZAxisMovement.h"
#include "Machine.h"

ZAxisMovementMode::ZAxisMovementMode()
{
}

ZAxisMovementMode::~ZAxisMovementMode()
{
}

void ZAxisMovementMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(4);
	machine->CloseClaw();
	machine->HandleRobotArm(1, 0, 3);
}

String ZAxisMovementMode::ToString()
{
	return MODE10;
}

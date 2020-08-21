#include "Mode23_ZAxisUpAndDown.h"
#include "Machine.h"

ZAxisUpAndDownMode::ZAxisUpAndDownMode()
{
}

ZAxisUpAndDownMode::~ZAxisUpAndDownMode()
{
}

void ZAxisUpAndDownMode::Initialize(Machine* machine)
{
	machine->Home(4);
}

void ZAxisUpAndDownMode::HandlePlaceholder(Machine* machine)
{
	machine->GetRobotArm().HandleZAxis(1);
	machine->GetRobotArm().HandleZAxis(0);
	machine->GetRobotArm().HandleZAxis(1);
	machine->GetRobotArm().HandleZAxis(0);
	machine->GetRobotArm().HandleZAxis(2);
	machine->GetControlPanel().Print("Z-Axis Mode", "Finished");
}

String ZAxisUpAndDownMode::ToString()
{
	return MODE23;
}
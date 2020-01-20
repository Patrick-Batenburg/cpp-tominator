#include "Mode9_HomeRobotArm.h"
#include "Machine.h"

HomeRobotArmMode::HomeRobotArmMode()
{
}

HomeRobotArmMode::~HomeRobotArmMode()
{
}

void HomeRobotArmMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(4);
	machine->GetControlPanel().Print("Homed: X, Y, Z, claw", "Finished");
}

String HomeRobotArmMode::ToString()
{
	return MODE9;
}
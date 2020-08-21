#include "Mode09_HomeRobotArm.h"
#include "Machine.h"

HomeRobotArmMode::HomeRobotArmMode()
{
}

HomeRobotArmMode::~HomeRobotArmMode()
{
}

void HomeRobotArmMode::Initialize(Machine* machine)
{
	machine->Home(4);
}

void HomeRobotArmMode::HandlePlaceholder(Machine* machine)
{
	machine->GetControlPanel().Print("Homed: X, Y, Z, claw", "Finished");
}

String HomeRobotArmMode::ToString()
{
	return MODE9;
}
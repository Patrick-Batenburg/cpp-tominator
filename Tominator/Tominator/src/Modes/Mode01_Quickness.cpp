#include "Mode01_Quickness.h"
#include "Machine.h"

QuicknessMode::QuicknessMode()
{
}

QuicknessMode::~QuicknessMode()
{
}

void QuicknessMode::Initialize(Machine* machine)
{
	machine->Home(5);
}

void QuicknessMode::HandlePlaceholder(Machine* machine)
{
	int columnThreeOffset = 100;
		
	for (int i = 0; i < 3; i++)
	{
		if(i == 1)
		{
			machine->GetRobotArm().HandleYAxisOffset(DirectionType::Forward);
		}
		else if (i == 2)
		{
			machine->GetRobotArm().HandleYAxisOffset(DirectionType::Forward, columnThreeOffset);
		}
		
		machine->GetRobotArm().HandleZAxis(2);
		machine->CloseClaw();
		machine->GetRobotArm().HandleZAxis(1);
		machine->GetRobotArm().HandleZAxis(2);
		machine->OpenClaw();
		machine->GetRobotArm().HandleZAxis(1);
		machine->GetRobotArm().HandleYAxis(i + 1);
	}	
}

String QuicknessMode::ToString()
{
	return MODE1;
}
#include "Mode05_ClawSortingMode.h"
#include "Machine.h"

ClawSortingMode::ClawSortingMode()
{
}

ClawSortingMode::~ClawSortingMode()
{
}

void ClawSortingMode::Initialize(Machine* machine)
{
	machine->Home(2); // Homes to default position. x:0, y:0
	machine->Home(5); // Home carriage
}

void ClawSortingMode::HandlePlaceholder(Machine* machine)
{
	WaterBalloon large = WaterBalloon(WaterBalloonType::Large, 2);
	WaterBalloon medium = WaterBalloon(WaterBalloonType::Medium, 1.5);
	WaterBalloon Small = WaterBalloon(WaterBalloonType::Small, 1);
	bool skipOffsetY = false;
	int columnThreeOffset = 100;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			bool isAtColumnTwo = j == 2;
			machine->GetRobotArm().HandleZAxis(2);
			machine->CloseClaw();
			machine->GetRobotArm().HandleZAxis(1);
			machine->GetRobotArm().HandleXAxis(3 - i);
			
			if (!skipOffsetY)
			{
				skipOffsetY = true;
				machine->GetRobotArm().HandleYAxisOffset(DirectionType::Forward);
			}
			
			machine->GetRobotArm().HandleYAxis(j);
			
			if (isAtColumnTwo)
			{
				machine->GetRobotArm().HandleYAxisOffset(DirectionType::Reverse, columnThreeOffset);
			}
			
			machine->OpenClaw();
			machine->GetRobotArm().HomeXAxis();
			
			if (j + 1 == 2)
			{
				machine->GetRobotArm().HandleYAxisOffset(DirectionType::Forward, columnThreeOffset);
			}
			
			if (isAtColumnTwo)
			{
				skipOffsetY = false;
				machine->GetRobotArm().HomeYAxis();
			}
			else
			{
				machine->GetRobotArm().HandleYAxis(j + 1);	
			}	
		}
	}
}

String ClawSortingMode::ToString()
{
	return MODE5;
}

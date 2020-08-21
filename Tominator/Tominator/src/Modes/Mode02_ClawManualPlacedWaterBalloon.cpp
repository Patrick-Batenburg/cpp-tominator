#include "Mode02_ClawManualPlacedWaterBalloon.h"
#include "Machine.h"

ClawManualPlacedWaterBalloonMode::ClawManualPlacedWaterBalloonMode()
{
}

ClawManualPlacedWaterBalloonMode::~ClawManualPlacedWaterBalloonMode()
{
}

void ClawManualPlacedWaterBalloonMode::Initialize(Machine* machine)
{
	int zAxisMiddleOffset = 5000;
	machine->Home(2); // Home carriage
	machine->Home(5); // Homes to default position. x:0, y:0
	machine->GetRobotArm().HandleZAxis(1, 0, zAxisMiddleOffset);
}

void ClawManualPlacedWaterBalloonMode::HandlePlaceholder(Machine* machine)
{
	int zAxisPlaceWaterBalloonOffset = 3000;
	static const char* types[] = { "Empty", "Small", "Medium", "Large", "Unkown" };
	
	for (int i = 0; i < 3; i++)
	{		
		delay(3000);
		machine->CloseClaw();
		delay(3000);
		machine->WeighWaterBalloon();
		machine->GetControlPanel().Print(types[machine->GetCurrentWaterBalloon().GetType()], String(machine->GetCurrentWaterBalloon().GetWeight()));	
		machine->GetRobotArm().HandleYAxisOffset(DirectionType::Forward);
		machine->GetRobotArm().HandleXAxis(3 - machine->GetConveyorBelt()->GetCurrentRow());	
		machine->GetRobotArm().HandleZAxisOffset(zAxisPlaceWaterBalloonOffset, HIGH);
		machine->OpenClaw();
		machine->GetRobotArm().HandleZAxisOffset(zAxisPlaceWaterBalloonOffset, LOW);
		machine->GetRobotArm().HomeXAxis();
		machine->GetRobotArm().HomeYAxis();
	}
	
	machine->GetFrame().HandleDCMotorOffset(true);
	machine->HandleFrame(DirectionType::Reverse);
	
	for (int i = 0; i < 3; i++)
	{
		machine->SortWaterBalloons();
	}

}

String ClawManualPlacedWaterBalloonMode::ToString()
{
	return MODE2;
}
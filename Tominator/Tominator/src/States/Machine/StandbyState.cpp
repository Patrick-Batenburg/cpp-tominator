#include "StandbyState.h"
#include "InitializeState.h"
#include "Machine.h"

StandbyState::StandbyState()
{
}

StandbyState::~StandbyState()
{
}

void StandbyState::Start(Machine* machine)
{
	machine->SetState(new InitializeState());
	machine->SetCurrentWaterBalloon(WaterBalloon());
	machine->SetConveyorBelt(ConveyorBelt());
	//machine->SelectMode(machine->GetControlPanel().GetRotaryEncoder().GetCounter());
	//machine->HomeRobotArm();

	if (DEBUG)
	{
		std::vector<std::vector<WaterBalloon>> waterBalloonPositions
		{
			{ WaterBalloon(WaterBalloonType::Unkown, 2),	WaterBalloon(WaterBalloonType::Unkown, 1),		WaterBalloon(WaterBalloonType::Unkown, 1.5) },
			{ WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1) },
			{ WaterBalloon(WaterBalloonType::Unkown, 1),	WaterBalloon(WaterBalloonType::Unkown, 2),		WaterBalloon(WaterBalloonType::Unkown, 2) }
		};
		
		machine->SetGrid(Grid(waterBalloonPositions));
	}
	else
	{
		machine->SetGrid(Grid());
	}

	digitalWrite(PIN_ENABLE_STEPPER_MOTOR, HIGH);
}

String StandbyState::ToString()
{
	return STANDBY_STATE;
}

#include "StandbyState.h"
#include "InitializeState.h"
#include "Machine.h"

using namespace std;

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
	machine->SetGrid(Grid());
	machine->SelectMode(machine->GetRotaryEncoder().GetCounter());

	if (DEBUG)
	{
		vector<vector<WaterBalloon>> waterBalloonPositions
		{
			{ WaterBalloon(WaterBalloonType::Unkown, 2),	WaterBalloon(WaterBalloonType::Unkown, 1),		WaterBalloon(WaterBalloonType::Unkown, 1.5) },
			{ WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1) },
			{ WaterBalloon(WaterBalloonType::Unkown, 1),	WaterBalloon(WaterBalloonType::Unkown, 2),		WaterBalloon(WaterBalloonType::Unkown, 2) }
		};

		machine->SetGrid(waterBalloonPositions);
	}
	
	digitalWrite(PIN_ENABLE_STEPPER_MOTOR, HIGH);
}

string StandbyState::ToString()
{
	return STANDBY_STATE;
}

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
	//digitalWrite(PIN_ENABLE_STEPPER_MOTOR, HIGH);
	//machine->SetCurrentWaterBalloon(WaterBalloon());
	//machine->SetConveyorBelt(ConveyorBelt());
	//machine->SetGrid(Grid());
	//machine->SelectMode(machine->GetRotaryEncoder().GetCounter());
	//machine->HomingRobotArm();

	//if (DEBUG)
	//{
		//vector<vector<WaterBalloon>> waterBalloonPositions
		//{
			//{ WaterBalloon(WaterBalloonType::Unkown, 2),	WaterBalloon(WaterBalloonType::Unkown, 1),		WaterBalloon(WaterBalloonType::Unkown, 1.5) },
			//{ WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1) },
			//{ WaterBalloon(WaterBalloonType::Unkown, 1),	WaterBalloon(WaterBalloonType::Unkown, 2),		WaterBalloon(WaterBalloonType::Unkown, 2) }
		//};
		//
		//Grid predeterminedGrid = Grid(waterBalloonPositions);
		//machine->SetGrid(predeterminedGrid);
	//}
}

String StandbyState::ToString()
{
	return STANDBY_STATE;
}

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
	machine->GetControlPanel().ConfigureInitializeLed();
	machine->SetCurrentWaterBalloon(WaterBalloon());
	machine->GetConveyorBelt()->Reset();
	machine->GetGrid()->Reset();
	machine->OpenClaw();
	machine->GetMode()->Initialize(machine);
	digitalWrite(PIN_ENABLE_STEPPER_MOTOR, HIGH);
}

String StandbyState::ToString()
{
	return STANDBY_STATE;
}

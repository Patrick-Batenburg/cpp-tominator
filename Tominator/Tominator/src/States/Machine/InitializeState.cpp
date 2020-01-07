#include "InitializeState.h"
#include "RunningState.h"
#include "Machine.h"
#include "TominatorVariables.h"

InitializeState::InitializeState()
{
	digitalWrite(PIN_ENABLE_STEPPER_MOTOR, HIGH);
}

InitializeState::~InitializeState()
{
}

void InitializeState::Start(Machine* machine)
{
	machine->SetState(new RunningState());
	machine->StartMode();
}

String InitializeState::ToString()
{
	return INITIALIZE_STATE;
}

#include "InitializeState.h"
#include "RunningState.h"
#include "Machine.h"
#include "TominatorVariables.h"

InitializeState::InitializeState()
{
}

InitializeState::~InitializeState()
{
}

void InitializeState::Start(Machine* machine)
{
	RunningState* state = new RunningState();
	machine->SetState(state);
	machine->StartMode();
	state->Finished();
}

String InitializeState::ToString()
{
	return INITIALIZE_STATE;
}

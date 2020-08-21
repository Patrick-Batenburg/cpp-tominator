#include "RunningState.h"
#include "Machine.h"
#include "BootUpState.h"

RunningState::RunningState()
{
}

RunningState::~RunningState()
{
}

void RunningState::Reset(Machine* machine)
{
	if(machine->GetState()->IsFinished())
	{
		machine->SetState(new BootUpState());
		machine->GetControlPanel().ConfigureBootUpLed();
	}
}

String RunningState::ToString()
{
	return RUNNING_STATE;
}

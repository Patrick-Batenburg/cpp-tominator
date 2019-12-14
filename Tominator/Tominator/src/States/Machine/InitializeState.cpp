#include "InitializeState.h"
#include "RunningState.h"
#include "Machine.h"
#include "TominatorVariables.h"

using namespace std;

InitializeState::InitializeState()
{
}

InitializeState::~InitializeState()
{
}

void InitializeState::Start(Machine* machine)
{
	machine->SetState(new RunningState());
	machine->StartMode();
}

string InitializeState::ToString()
{
	return INITIALIZE_STATE;
}

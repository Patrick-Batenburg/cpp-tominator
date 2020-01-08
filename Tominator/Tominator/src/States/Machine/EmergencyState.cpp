#include "EmergencyState.h"
#include "RunningState.h"
#include "Machine.h"
#include "TominatorVariables.h"
#include "BootUpState.h"

EmergencyState::EmergencyState()
{
}

EmergencyState::~EmergencyState()
{
}

void EmergencyState::Reset(Machine* machine)
{
	machine->SetState(new BootUpState());
}

String EmergencyState::ToString()
{
	return EMERGENCY_STATE;
}

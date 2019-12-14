#include "BaseMachineState.h"
#include "BootUpState.h"
#include "Machine.h"

using namespace std;

BaseMachineState::BaseMachineState()
{
}

BaseMachineState::~BaseMachineState()
{
}

void BaseMachineState::Start(Machine* machine)
{
}

void BaseMachineState::Reset(Machine* machine)
{
}

void BaseMachineState::EmergencyStop(Machine* machine)
{
	digitalWrite(PIN_ENABLE_STEPPER_MOTOR, LOW);
	machine->SetState(new BootUpState());
}

string BaseMachineState::ToString()
{
	return BASE_MACHINE_STATE;
}

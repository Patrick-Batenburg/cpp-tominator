#include "BootUpState.h"
#include "StandbyState.h"
#include "Machine.h"

using namespace std;

BootUpState::BootUpState()
{
	digitalWrite(PIN_ENABLE_STEPPER_MOTOR, LOW);
}

BootUpState::~BootUpState()
{
}

void BootUpState::Reset(Machine* machine)
{
	machine->SetState(new StandbyState());
}

string BootUpState::ToString()
{
	return BOOT_UP_STATE;
}

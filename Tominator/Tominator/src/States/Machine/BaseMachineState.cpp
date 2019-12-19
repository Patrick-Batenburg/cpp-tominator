#include "BaseMachineState.h"
#include "BootUpState.h"
#include "Machine.h"

using namespace std;

BaseMachineState::BaseMachineState()
{
	this->stateTypes[BASE_MACHINE_STATE] = BaseMachineStateType::BaseMachineType;
	this->stateTypes[BOOT_UP_STATE] = BaseMachineStateType::BootUpStateType;
	this->stateTypes[STANDBY_STATE] = BaseMachineStateType::StandbyStateType;
	this->stateTypes[INITIALIZE_STATE] = BaseMachineStateType::InitializeStateType;
	this->stateTypes[RUNNING_STATE] = BaseMachineStateType::RunningStateType;
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

std::map<std::string, BaseMachineStateType> BaseMachineState::GetStateTypes()
{
	return this->stateTypes;
}

string BaseMachineState::ToString()
{
	return BASE_MACHINE_STATE;
}

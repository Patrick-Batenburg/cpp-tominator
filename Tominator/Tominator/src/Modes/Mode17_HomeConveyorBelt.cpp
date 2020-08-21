#include "Mode17_HomeConveyorBelt.h"
#include "Machine.h"

HomeConveyorBeltMode::HomeConveyorBeltMode()
{
}

HomeConveyorBeltMode::~HomeConveyorBeltMode()
{
}

void HomeConveyorBeltMode::Initialize(Machine* machine)
{

}

void HomeConveyorBeltMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(3);
}

String HomeConveyorBeltMode::ToString()
{
	return MODE17;
}

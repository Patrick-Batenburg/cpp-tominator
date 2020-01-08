#include "BaseMode.h"
#include "Machine.h"

BaseMode::BaseMode()
{
}

BaseMode::~BaseMode()
{
}

void BaseMode::Execute(Machine* machine)
{
	this->HandlePlaceholder(machine);
}

String BaseMode::ToString()
{
	return BASE_MODE;
}

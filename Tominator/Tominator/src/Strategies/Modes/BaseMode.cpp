#include "BaseMode.h"
#include "Machine.h"

using namespace std;

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

string BaseMode::ToString()
{
	return BASE_MODE;
}

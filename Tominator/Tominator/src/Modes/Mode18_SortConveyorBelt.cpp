#include "Mode18_SortConveyorBelt.h"
#include "Machine.h"

SortConveyorBeltMode::SortConveyorBeltMode()
{
}

SortConveyorBeltMode::~SortConveyorBeltMode()
{
}

void SortConveyorBeltMode::HandlePlaceholder(Machine* machine)
{
	machine->GetConveyorBelt()->Sort();
}

String SortConveyorBeltMode::ToString()
{
	return MODE18;
}

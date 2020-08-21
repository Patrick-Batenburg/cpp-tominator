#include "Mode18_ConveyorBeltSorting.h"
#include "Machine.h"

ConveyorBeltSortingMode::ConveyorBeltSortingMode()
{
}

ConveyorBeltSortingMode::~ConveyorBeltSortingMode()
{
}

void ConveyorBeltSortingMode::Initialize(Machine* machine)
{

}

void ConveyorBeltSortingMode::HandlePlaceholder(Machine* machine)
{
	machine->GetConveyorBelt()->Sort();
}

String ConveyorBeltSortingMode::ToString()
{
	return MODE18;
}

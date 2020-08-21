#include "Mode21_SortingSideSimulation.h"
#include "Machine.h"

SortingSideSimulationMode::SortingSideSimulationMode()
{
}

SortingSideSimulationMode::~SortingSideSimulationMode()
{
}

void SortingSideSimulationMode::Initialize(Machine* machine)
{
	machine->Home(2);
}

void SortingSideSimulationMode::HandlePlaceholder(Machine* machine)
{
	machine->SortWaterBalloons();
	machine->SortWaterBalloons();
	machine->SortWaterBalloons();
}

String SortingSideSimulationMode::ToString()
{
	return MODE21;
}

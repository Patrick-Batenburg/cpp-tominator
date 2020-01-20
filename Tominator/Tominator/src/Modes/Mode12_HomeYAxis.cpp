#include "Mode12_HomeYAxis.h"
#include "Machine.h"

HomeYAxisMode::HomeYAxisMode()
{
}

HomeYAxisMode::~HomeYAxisMode()
{
}

void HomeYAxisMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(7);
}

String HomeYAxisMode::ToString()
{
	return MODE12;
}

#include "Mode11_HomeXAxis.h"
#include "Machine.h"

HomeXAxisMode::HomeXAxisMode()
{
}

HomeXAxisMode::~HomeXAxisMode()
{
}

void HomeXAxisMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(6);
}

String HomeXAxisMode::ToString()
{
	return MODE11;
}

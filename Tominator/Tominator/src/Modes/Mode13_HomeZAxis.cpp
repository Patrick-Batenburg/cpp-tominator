#include "Mode13_HomeZAxis.h"
#include "Machine.h"

HomeZAxisMode::HomeZAxisMode()
{
}

HomeZAxisMode::~HomeZAxisMode()
{
}

void HomeZAxisMode::Initialize(Machine* machine)
{

}

void HomeZAxisMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(8);
}

String HomeZAxisMode::ToString()
{
	return MODE13;
}

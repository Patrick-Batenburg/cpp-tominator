#include "Mode14_HomeClaw.h"
#include "Machine.h"

HomeClawMode::HomeClawMode()
{
}

HomeClawMode::~HomeClawMode()
{
}

void HomeClawMode::Initialize(Machine* machine)
{

}

void HomeClawMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(9);
}

String HomeClawMode::ToString()
{
	return MODE14;
}

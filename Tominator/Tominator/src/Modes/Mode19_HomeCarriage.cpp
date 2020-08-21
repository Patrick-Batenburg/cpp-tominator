#include "Mode19_HomeCarriage.h"
#include "Machine.h"

HomeCarriageMode::HomeCarriageMode()
{
}

HomeCarriageMode::~HomeCarriageMode()
{
}

void HomeCarriageMode::Initialize(Machine* machine)
{

}

void HomeCarriageMode::HandlePlaceholder(Machine* machine)
{
	machine->Home(2);
}

String HomeCarriageMode::ToString()
{
	return MODE19;
}

#include "Mode20_HomeCarriageToTop.h"
#include "Machine.h"

HomeCarriageToTopMode::HomeCarriageToTopMode()
{
}

HomeCarriageToTopMode::~HomeCarriageToTopMode()
{
}

void HomeCarriageToTopMode::Initialize(Machine* machine)
{

}

void HomeCarriageToTopMode::HandlePlaceholder(Machine* machine)
{
	machine->GetCarriage().HandleDCMotor(100, 33);
}

String HomeCarriageToTopMode::ToString()
{
	return MODE20;
}

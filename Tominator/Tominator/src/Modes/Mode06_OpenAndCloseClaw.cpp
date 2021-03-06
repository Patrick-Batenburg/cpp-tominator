#include "Mode06_OpenAndCloseClaw.h"
#include "Machine.h"

OpenAndCloseClawMode::OpenAndCloseClawMode()
{
}

OpenAndCloseClawMode::~OpenAndCloseClawMode()
{
} 

void OpenAndCloseClawMode::Initialize(Machine* machine)
{

}

void OpenAndCloseClawMode::HandlePlaceholder(Machine* machine)
{
	machine->OpenClaw();
	machine->CloseClaw();
}

String OpenAndCloseClawMode::ToString()
{
	return MODE6;
}

#include "Mode6_OpenAndCloseClaw.h"
#include "Machine.h"

using namespace std;

OpenAndCloseClawMode::OpenAndCloseClawMode()
{
}

OpenAndCloseClawMode::~OpenAndCloseClawMode()
{
} 

void OpenAndCloseClawMode::HandlePlaceholder(Machine* machine)
{
	machine->OpenClaw();
	machine->CloseClaw();
}

string OpenAndCloseClawMode::ToString()
{
	return MODE6;
}

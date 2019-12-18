#include "Mode7_DriveFrameBackAndForth.h"
#include "Machine.h"

using namespace std;

DriveFrameBackAndForthMode::DriveFrameBackAndForthMode()
{
}

DriveFrameBackAndForthMode::~DriveFrameBackAndForthMode()
{
}

void DriveFrameBackAndForthMode::HandlePlaceholder(Machine* machine)
{
	machine->TurnOnFrameMotor(DirectionType::Forward);
	machine->HandleFrame(DirectionType::Forward);
	machine->HandleFrame(DirectionType::Reverse);
}

string DriveFrameBackAndForthMode::ToString()
{
	return MODE7;
}
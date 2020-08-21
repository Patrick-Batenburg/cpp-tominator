#include "Mode07_DriveFrameBackAndForth.h"
#include "Machine.h"

DriveFrameBackAndForthMode::DriveFrameBackAndForthMode()
{
}

DriveFrameBackAndForthMode::~DriveFrameBackAndForthMode()
{
}

void DriveFrameBackAndForthMode::Initialize(Machine* machine)
{
	machine->TurnOnFrameMotor(DirectionType::Forward);
}

void DriveFrameBackAndForthMode::HandlePlaceholder(Machine* machine)
{
	machine->HandleFrame(DirectionType::Forward);
	machine->HandleFrame(DirectionType::Reverse);
}

String DriveFrameBackAndForthMode::ToString()
{
	return MODE7;
}
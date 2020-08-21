#include "Mode15_CarriageBeyondTopSensor.h"
#include "Machine.h"

CarriageBeyondTopSensorMode::CarriageBeyondTopSensorMode()
{
}

CarriageBeyondTopSensorMode::~CarriageBeyondTopSensorMode()
{
}

void CarriageBeyondTopSensorMode::Initialize(Machine* machine)
{
	machine->GetCarriage().GetDCMotor()->Start(DirectionType::Forward);
	machine->GetCarriage().GetDCMotor()->SetSpeedInPercentage(100);
}

void CarriageBeyondTopSensorMode::HandlePlaceholder(Machine* machine)
{
	// Unsafe. Mostly useful for storing the robot in a compact manner. Press emergency stop when at desired level.
	machine->GetCarriage().GetDCMotor()->Run();
}

String CarriageBeyondTopSensorMode::ToString()
{
	return MODE15;
}

#include "Mode16_SerialPrintSimulation.h"
#include "Machine.h"

SerialPrintSimulationMode::SerialPrintSimulationMode()
{
}

SerialPrintSimulationMode::~SerialPrintSimulationMode()
{
}

String SerialPrintSimulationMode::ToString(WaterBalloonType value)
{
	switch (value)
	{
		case WaterBalloonType::Empty:
		return "Empty";
		case WaterBalloonType::Small:
		return "Small";
		case WaterBalloonType::Medium:
		return "Medium";
		case WaterBalloonType::Large:
		return "Large";
		case WaterBalloonType::Unkown:
		return "Unkown";
		default:
		return "No value";
	}
}

void SerialPrintSimulationMode::HandlePlaceholder(Machine* machine)
{	
	std::vector<std::vector<WaterBalloon>> waterBalloonPositions
	{
		{ WaterBalloon(WaterBalloonType::Unkown, 2),	WaterBalloon(WaterBalloonType::Unkown, 1),		WaterBalloon(WaterBalloonType::Unkown, 1.5) },
		{ WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1.5),	WaterBalloon(WaterBalloonType::Unkown, 1) },
		{ WaterBalloon(WaterBalloonType::Unkown, 1),	WaterBalloon(WaterBalloonType::Unkown, 2),		WaterBalloon(WaterBalloonType::Unkown, 2) }
	};
	
	machine->GetGrid()->SetWaterBalloonPositions(waterBalloonPositions);

	String row = "Row 1: ";
	Serial.println("State Test:");
	Serial.print("Current state: " + machine->GetState()->ToString());
	Serial.println();
	Serial.println();
	
	machine->ResetButtonPressed();
	Serial.print("Current state: " + machine->GetState()->ToString());
	Serial.println();
	Serial.println();
	
	machine->StartButtonPressed();
	Serial.print("Current state: " + machine->GetState()->ToString());
	Serial.println();
	Serial.println();
	
	//machine->EmergencyStopButtonPressed();
	//Serial.print("Current state: " + machine->GetState()->ToString());
	//Serial.println();
	//Serial.println();
	
	machine->StartButtonPressed();
	Serial.print("Current state: " + machine->GetState()->ToString());
	Serial.println();
	Serial.println();
	
	//machine->EmergencyStopButtonPressed();
	//Serial.print("Current state: " + machine->GetState()->ToString());
	//Serial.println();
	//Serial.println();
	
	Serial.println("Grid Before");
	
	for (int i = 0; i < machine->GetGrid()->GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine->GetGrid()->GetWaterBalloonPositions()[i].size(); j++)
		{
			WaterBalloon waterBalloon = WaterBalloon(machine->GetGrid()->GetWaterBalloonPositions()[i][j].GetWeight());
			Serial.print(waterBalloon.GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println("Conveyor Belt:");
	
	for (int i = 0; i < machine->GetConveyorBelt()->GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine->GetConveyorBelt()->GetWaterBalloonPositions()[i].size(); j++)
		{
			Serial.print(machine->GetConveyorBelt()->GetWaterBalloonPositions()[i][j].GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println("Grid After:");
	
	for (int i = 0; i < machine->GetGrid()->GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine->GetGrid()->GetWaterBalloonPositions()[i].size(); j++)
		{
			Serial.print(machine->GetGrid()->GetWaterBalloonPositions()[i][j].GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println(row + ToString(machine->GetConveyorBelt()->GetFirstRowType()));
	
	row = "Row 2: ";
	Serial.println(row + ToString(machine->GetConveyorBelt()->GetSecondRowType()));
	
	row = "Row 3: ";
	Serial.println(row + ToString(machine->GetConveyorBelt()->GetThirdRowType()));
	Serial.println();
	Serial.print("transported water balloons: ");
	Serial.println(machine->GetConveyorBelt()->GetTransportedWaterBalloons());
	Serial.println();

	machine->EmergencyStopButtonPressed();
	Serial.print("Current state: " + machine->GetState()->ToString());
	Serial.println();
	Serial.println();
	machine->ResetButtonPressed();
}

String SerialPrintSimulationMode::ToString()
{
	return MODE15;
}

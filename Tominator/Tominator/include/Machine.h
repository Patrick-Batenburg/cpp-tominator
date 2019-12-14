#pragma once
#include "BaseMachineState.h"
#include "BaseMode.h"
#include "WaterBalloon.h"
#include "DCMotor.h"
#include "RotaryEncoder.h"
#include "BaseGrid.h"
#include "Grid.h"
#include "ConveyorBelt.h"
#include "RobotArm.h"
#include "Carriage.h"
#include "Frame.h"
#include <HX711.h>

class Machine
{
private:
	static long const loadCellOffset = 50682624;
	static long const loadCellDivider = 5895655;
	HX711 loadCell;
	WaterBalloon currentWaterBalloon;
	BaseMachineState* state;
	BaseMode* mode;
	Grid grid;
	ConveyorBelt conveyorBelt;
	RobotArm robotArm;
	RotaryEncoder rotaryEncoder;
	Carriage carriage;
	Frame frame;

public:
	Machine();
	~Machine();
	Machine(std::vector<std::vector<WaterBalloon>> waterBalloonPositions);
	void StartMode();
	void SelectMode(int value);
	void StartButtonPressed();
	void ResetButtonPressed();
	void EmergencyStopButtonPressed();
	void SortWaterBalloons();
	void WeighWaterBalloon();
	void OpenClaw();
	void CloseClaw();
	
	void HandleArm(int x, int y, int z);
	
	void TurnOnFrameMotor(DirectionType direction);
	void TurnOffFrameMotor();
	void TurnOnCarriageMotor(DirectionType direction);
	void TurnOffCarriageMotor();
	void TurnOnConveyorBeltMotor(DirectionType direction);
	void TurnOffConveyorBeltMotor();
	
	WaterBalloon GetCurrentWaterBalloon();
	void SetCurrentWaterBalloon(WaterBalloon value);
	BaseMachineState* GetState();
	void SetState(BaseMachineState* value);
	BaseMode* GetMode();
	void SetMode(BaseMode* value);
	Grid GetGrid();
	void SetGrid(Grid value);
	ConveyorBelt GetConveyorBelt();
	void SetConveyorBelt(ConveyorBelt value);
	RotaryEncoder GetRotaryEncoder();
};

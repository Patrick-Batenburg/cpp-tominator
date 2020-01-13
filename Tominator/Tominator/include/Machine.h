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
#include "ControlPanel.h"
#include <HX711.h>
#include <LiquidCrystal_I2C.h>

class Machine
{
private:
	WaterBalloon currentWaterBalloon;
	BaseMachineState* state;
	BaseMode* mode;
	Grid* grid;
	ConveyorBelt* conveyorBelt;
	Frame frame;
	Carriage carriage;
	RobotArm robotArm;
	HX711 loadCell;
	ControlPanel controlPanel;

public:
	/**
		Initializes a new instance of the Machine class.
	*/
	Machine();

	/**
		Initializes a new instance of the Machine class.

		@param grid			The grid with water balloon positions.
		@param conveyorBelt The conveyorBelt with water balloon positions.
		@param frame		The frame of the machine.
		@param carriage		The carriage of the machine.
		@param robotArm		The robot arm of the machine.
		@param loadCell		The load cell for weighting water balloons.
		@param controlPanel The control panel of the machine.
	*/
	Machine(Grid* grid, ConveyorBelt* conveyorBelt, Frame frame, Carriage carriage, RobotArm robotArm, HX711 loadCell, ControlPanel controlPanel);
	/**
		Deconstruct the instance of the Machine class.
	*/
	~Machine();

	/**
		Executes a set of instructions defined in a mode as long the machine resides in the correct state.
	*/
	void StartMode();
	
	/**
		Sets the machine's selected mode based on int-value.

		@param value The new selected mode.
	*/
	void SelectMode(int value);

	/**
		Indicates that the start button was pressed. Calls underlying Start() method in the state the machine resides in. May lead to a state change.
	*/
	void StartButtonPressed();

	/**
		Indicates that the reset button was pressed. Calls underlying Reset() method in the state the machine resides in. May lead to a state change.
	*/
	void ResetButtonPressed();

	/**
		Indicates that the emergency stop button was pressed. Calls underlying EmergencyStop() method in the state the machine resides in. Leads to a guranteed state change (BootUpState).
	*/
	void EmergencyStopButtonPressed();

	/**
		Sorts the water balloons present on the conveyor belt. First the carriage is handled to be on the correct height before any actual sorting can take place.
	*/
	void SortWaterBalloons();

	/**
		Weigh the grabbed/placed water balloon in the claw.
	*/
	void WeighWaterBalloon();

	/**
		Opens the robot arm's claw.
	*/
	void OpenClaw();

	/**
		Closes the robot arm's claw.
	*/
	void CloseClaw();
	
	/**
		Handles the frame to reach its destination.
		
		@param direction The direction the frame needs to go to.
	*/
	void HandleFrame(DirectionType direction);

	/**
		Handles the X, Y and Z-axis of the robot arm.

		@param x The X-axis the robot needs to go to.
		@param y The Y-axis the robot needs to go to.
		@param z The Z-axis the robot needs to go to.
	*/
	void HandleRobotArm(int x, int y, int z);

	/**
		Applies homing to the robot arm. By default it will home the X, Y, Z-axis and claw simultaneously.
		
		@param homeWhat Indicates what needs homing based on int-value.
		0 = Homing is applied to the X, Y, Z-axis and claw (default).
		1 = Homing is only applied to the X, Y and Z-axis
		2 = Homing is only applied to the claw.
	*/
	void HomeRobotArm(int homeWhat = 0);
	
	/**
		Turns the frame's DC motor on.

		@param direction The direction the DC motor starts in.
	*/
	void TurnOnFrameMotor(DirectionType direction);

	/**
		Turns the frame's DC motor off.
	*/	
	void TurnOffFrameMotor();

	/**
		Turns the frame's DC motor on.

		@param direction The direction the DC motor starts in.
	*/	
	void TurnOnCarriageMotor(DirectionType direction);

	/**
		Turns the carriage's DC motor off.
	*/	
	void TurnOffCarriageMotor();

	/**
		Turns the frame's DC motor on.

		@param direction The direction the DC motor starts in.
	*/
	void TurnOnConveyorBeltMotor(DirectionType direction);

	/**
		Turns the conveyor belt's DC motor off.
	*/	
	void TurnOffConveyorBeltMotor();

	/**
		Gets the current grabbed water balloon.
		
		@return The current grabbed water balloon.
	*/	
	WaterBalloon GetCurrentWaterBalloon();

	/**
		Sets the current grabbed water balloon.
		
		@param value The new grabbed water balloon.
	*/
	void SetCurrentWaterBalloon(WaterBalloon value);

	/**
		Gets the current state of the machine.
		
		@return The current state of the machine.
	*/
	BaseMachineState* GetState();

	/**
		Sets the current state of the machine.
		
		@param value The new state of the machine.
	*/
	void SetState(BaseMachineState* value);

	/**
		Gets the current selected mode.
		
		@return The current selected mode.
	*/
	BaseMode* GetMode();

	/**
		Sets the machine's selected mode.

		@param value The new selected mode.
	*/
	void SetMode(BaseMode* value);

	/**
		Gets the grid object.
		
		@return The grid object.
	*/
	Grid* GetGrid();

	/**
		Gets the conveyor belt object.
		
		@return The conveyor belt object.
	*/
	ConveyorBelt* GetConveyorBelt();

	/**
		Gets the control panel object.
		
		@return The control panel object.
	*/	
	ControlPanel GetControlPanel();
};

#include "Machine.h"
#include "BootUpState.h"
#include "TominatorPins.h"
#include <LiquidCrystal_I2C.h>
#include "NoneRowEmptyState.h"
#include "Mode00_Default.h"
#include "Mode01_Quickness.h"
#include "Mode02_ClawManualPlacedWaterBalloon.h"
#include "Mode03_GrabWaterBalloon.h"
#include "Mode04_PlaceWaterballoonOnConveyorBelt.h"
#include "Mode05_ClawSortingMode.h"
#include "Mode06_OpenAndCloseClaw.h"
#include "Mode07_DriveFrameBackAndForth.h"
#include "Mode08_SwitchingModes.h"
#include "Mode09_HomeRobotArm.h"
#include "Mode10_ZAxisMovement.h"
#include "Mode11_HomeXAxis.h"
#include "Mode12_HomeYAxis.h"
#include "Mode13_HomeZAxis.h"
#include "Mode14_HomeClaw.h"
#include "Mode15_CarriageBeyondTopSensor.h"
#include "Mode16_SerialPrintSimulation.h"
#include "Mode17_HomeConveyorBelt.h"
#include "Mode18_ConveyorBeltSorting.h"
#include "Mode19_HomeCarriage.h"
#include "Mode20_HomeCarriageToTop.h"
#include "Mode21_SortingSideSimulation.h"
#include "Mode22_FrameSortingSideOffset.h"
#include "Mode23_ZAxisUpAndDown.h"

Machine::Machine()
{
	this->mode = new DefaultMode();
	this->state = new BootUpState();
	this->currentWaterBalloon = WaterBalloon();
}

Machine::Machine(Grid* grid, ConveyorBelt* conveyorBelt, Frame frame, Carriage carriage, RobotArm robotArm, HX711 loadCell, ControlPanel controlPanel) : Machine()
{
	this->grid = grid;
	this->conveyorBelt = conveyorBelt;
	this->frame = frame;
	this->carriage = carriage;
	this->robotArm = robotArm;
	this->loadCell = loadCell;
	this->controlPanel = controlPanel;
	this->controlPanel.Print(this->GetState()->ToString(), this->GetMode()->ToString());
}

Machine::~Machine()
{
}

void Machine::StartMode()
{
	this->controlPanel.Print(this->GetState()->ToString(), this->GetMode()->ToString());
	
	if (this->state->ToString() == RUNNING_STATE)
	{
		this->mode->Execute(this);
	}
}

void Machine::SelectMode(int value)
{
	if (this->state->ToString() == STANDBY_STATE && this->rotaryEncoderCounter != this->GetControlPanel().GetRotaryEncoder()->GetCounter())
	{
		switch (value)
		{
			case 1:
				this->SetMode(new QuicknessMode());
				break;
			case 2:
				this->SetMode(new ClawManualPlacedWaterBalloonMode());
				break;
			case 3:
				this->SetMode(new GrabWaterBalloonMode());
				break;
			case 4:
				this->SetMode(new PlaceWaterballoonOnConveyorBeltMode());
				break;
			case 5:
				this->SetMode(new ClawSortingMode());
				break;
			case 6:
				this->SetMode(new OpenAndCloseClawMode());
				break;
			case 7:
				this->SetMode(new DriveFrameBackAndForthMode());
				break;
			case 8:
				this->SetMode(new SwitchingModesMode());
				break;
			case 9:
				this->SetMode(new HomeRobotArmMode());
				break;
			case 10:
				this->SetMode(new ZAxisMovementMode());
				break;
			case 11:
				this->SetMode(new HomeXAxisMode());
				break;
			case 12:
				this->SetMode(new HomeYAxisMode());
				break;
			case 13:
				this->SetMode(new HomeZAxisMode());
				break;
			case 14:
				this->SetMode(new HomeClawMode());
				break;
			case 15:
				// Unsafe. Mostly useful for storing the robot in a compact manner. Press emergency stop when at desired level.
				this->SetMode(new CarriageBeyondTopSensorMode());
				break;
			case 16:
				this->SetMode(new SerialPrintSimulationMode());
				break;
			case 17:
				this->SetMode(new HomeConveyorBeltMode());
				break;
			case 18:
				this->SetMode(new ConveyorBeltSortingMode());
				break;
			case 19:
				this->SetMode(new HomeCarriageMode());
				break;
			case 20:
				this->SetMode(new HomeCarriageToTopMode());
				break;
			case 21:
				this->SetMode(new SortingSideSimulationMode());
				break;
			case 22:
				this->SetMode(new FrameSortingSideOffsetMode());
				break;				
			case 23:
				this->SetMode(new ZAxisUpAndDownMode());
				break;
			case 0:
			default:
				this->SetMode(new DefaultMode());
				break;
		}
	}
	
	this->rotaryEncoderCounter = this->GetControlPanel().GetRotaryEncoder()->GetCounter();
}

void Machine::StartButtonPressed()
{
	this->state->Start(this);
}

void Machine::ResetButtonPressed()
{
	this->state->Reset(this);
}

void Machine::EmergencyStopButtonPressed()
{
	this->state->EmergencyStop(this);
}

void Machine::SortWaterBalloons()
{
	// 0 = Bottom
	// 1 = Middle
	// 2 = Top
	int sortingArea = 0;
	int conveyorBeltSpeed = 50;
	int carriageSpeed = 100;
	this->conveyorBelt->GetDCMotor()->SetSpeed(conveyorBeltSpeed);
	this->carriage.GetDCMotor()->SetSpeed(carriageSpeed);

	switch (this->conveyorBelt->GetState()->GetStateTypes()[this->conveyorBelt->GetState()->ToString()])
	{
		case BaseGridStateType::FirstRowEmptyStateType:
			sortingArea = 1;
			break;
		case BaseGridStateType::SecondRowEmptyStateType:
			sortingArea = 2;
			break;
		case BaseGridStateType::BaseGridType:
		case BaseGridStateType::NoneRowEmptyStateType:
		default:
			sortingArea = 0;
			break;
	}

	switch (sortingArea)
	{
		case 0:
			this->carriage.HandleDCMotor(carriageSpeed, HALL_CARRIAGE_BOTTOM);
			break;
		case 1:
			this->carriage.HandleDCMotor(carriageSpeed, HALL_CARRIAGE_MIDDLE);
			break;
		case 2:
			this->carriage.HandleDCMotor(carriageSpeed, HALL_CARRIAGE_TOP);
			break;
		default:
			break;
	}
	
	if (sortingArea != 0)
	{
		this->GetFrame().HandleDCMotorOffset(false);
	}
	
	this->conveyorBelt->Sort();
	this->conveyorBelt->GetState()->Next(conveyorBelt);
}

void Machine::WeighWaterBalloon()
{
	float weight = this->loadCell.get_units();
	this->currentWaterBalloon.SetWeight(weight);
	
	while (this->currentWaterBalloon.GetType() == WaterBalloonType::Unkown)
	{
		weight = this->loadCell.get_units();
		this->currentWaterBalloon.SetWeight(weight);
	}
	
	if (this->conveyorBelt->CanAddWaterBalloon(this->currentWaterBalloon))
	{
		this->conveyorBelt->AddWaterBalloon(this->currentWaterBalloon);
		this->grid->SelectNextPosition();
	}
}

void Machine::CloseClaw()
{
	this->robotArm.CloseClaw();
}

void Machine::OpenClaw()
{
	this->robotArm.OpenClaw();
}

void Machine::HandleFrame(DirectionType direction)
{
	this->frame.HandleDCMotor(direction);
}

void Machine::HandleRobotArm(int x, int y, int z)
{
	int negative = -1;
	
	if (x != negative)
	{
		this->robotArm.HandleXAxis(x);
	}
	
	if (y != negative)
	{
		this->robotArm.HandleYAxis(y);
	}

	if (z != negative)
	{
		this->robotArm.HandleZAxis(z);
	}	
}

void Machine::Home(int homeWhat)
{	
	switch (homeWhat)
	{
		case 0:
		default:
			this->frame.Home();
			this->carriage.Home();
			this->conveyorBelt->Home();
			this->robotArm.Home();
			break;
		case 1:
			this->frame.Home();
			break;
		case 2:
			this->carriage.Home();
			break;
		case 3:
			this->conveyorBelt->Home();
			break;
		case 4:
			this->robotArm.Home();
			break;
		case 5:
			this->robotArm.Home(1);
			break;
		case 6:
			this->robotArm.HomeXAxis();
			break;
		case 7:
			this->robotArm.HomeYAxis();
			break;
		case 8:
			this->robotArm.HomeZAxis();
			break;
		case 9:
			this->robotArm.OpenClaw();
			break;
	}
}

void Machine::TurnOnFrameMotor(DirectionType direction)
{
	this->frame.GetDCMotor()->Start(direction);
}

void Machine::TurnOffFrameMotor()
{
	this->frame.GetDCMotor()->Stop();
}

void Machine::TurnOnCarriageMotor(DirectionType direction)
{
	this->carriage.GetDCMotor()->Start(direction);
}

void Machine::TurnOffCarriageMotor()
{
	this->carriage.GetDCMotor()->Stop();
}

void Machine::TurnOnConveyorBeltMotor(DirectionType direction)
{
	this->conveyorBelt->GetDCMotor()->Start(direction);
}

void Machine::TurnOffConveyorBeltMotor()
{
	this->conveyorBelt->GetDCMotor()->Stop();
}

BaseMachineState* Machine::GetState()
{
	return this->state;
}

void Machine::SetState(BaseMachineState* value)
{
	delete this->state;
	this->state = value;
	this->controlPanel.Print(this->GetState()->ToString(), this->GetMode()->ToString());
}

BaseMode* Machine::GetMode()
{
	return this->mode;
}

void Machine::SetMode(BaseMode* value)
{
	delete this->mode;
	this->mode = value;
	this->controlPanel.Print(this->GetState()->ToString(), this->GetMode()->ToString());
}

Grid* Machine::GetGrid()
{
	return this->grid;
}

ConveyorBelt* Machine::GetConveyorBelt()
{
	return this->conveyorBelt;
}

ControlPanel Machine::GetControlPanel()
{
	return this->controlPanel;
}

Carriage Machine::GetCarriage()
{
	return this->carriage;
}

Frame Machine::GetFrame()
{
	return this->frame;
}

RobotArm Machine::GetRobotArm()
{
	return this->robotArm;
}

WaterBalloon Machine::GetCurrentWaterBalloon()
{
	return this->currentWaterBalloon;
}

void Machine::SetCurrentWaterBalloon(WaterBalloon value)
{
	this->currentWaterBalloon = value;
}

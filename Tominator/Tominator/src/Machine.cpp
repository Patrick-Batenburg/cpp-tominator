#include "Machine.h"
#include "DCMotor.h"
#include "BootUpState.h"
#include "Mode0_Default.h"
#include "Mode1_ClawManualPlacedWaterBalloon.h"
#include "Mode2_Quickness.h"
#include "Mode3_GrabWaterBalloon.h"
#include "Mode4_PlaceWaterballoonOnConveyorBelt.h"
#include "Mode5_Sorting.h"
#include "TominatorPins.h"

using namespace std;

Machine::Machine()
{
	DCMotor conveyorBeltDCMotor = DCMotor(PIN_CONVEYOR_BELT_IN1_DIRECTION, PIN_CONVEYOR_BELT_IN2_DIRECTION, PIN_CONVEYOR_BELT_PWM);
	DCMotor carriageDCMotor = DCMotor(PIN_CARRIAGE_IN1_DIRECTION, PIN_CARRIAGE_IN2_DIRECTION, PIN_CARRIAGE_PWM);
	DCMotor frameDCMotor = DCMotor(PIN_FRAME_IN1_DIRECTION, PIN_FRAME_IN2_DIRECTION, PIN_FRAME_PWM);
	UltrasonicSensor gridSideSensor = UltrasonicSensor(B1_ULTRASONIC_TRIGGER, B1_ULTRASONIC_ECHO);
	UltrasonicSensor sortingSideSensor = UltrasonicSensor(B2_ULTRASONIC_TRIGGER, B2_ULTRASONIC_ECHO);
	Claw claw = Claw(STP_CLAW_PULSE, STP_CLAW_DIRECTION, REED9_HOMING_CLAW);
	this->mode = new DefaultMode();
	this->state = new BootUpState();
	this->currentWaterBalloon = WaterBalloon();
	this->grid = Grid();
	this->controlPanel = ControlPanel(PIN_START_BUTTON, PIN_RESET_BUTTON, PIN_EMERGENCY_STOP_BUTTON);
	this->conveyorBelt = ConveyorBelt(conveyorBeltDCMotor, REED3_CONVEYOR_BELT);	
	this->carriage = Carriage(carriageDCMotor, HALL_CARRIAGE_BOTTOM, HALL_CARRIAGE_MIDDLE, HALL_CARRIAGE_TOP);
	this->frame = Frame(frameDCMotor, gridSideSensor, sortingSideSensor, REED1_GRID_SIDE, REED2_SORTING_SIDE, &this->grid, &this->conveyorBelt);
	this->robotArm = RobotArm(STP_X_PULSE, STP_X_DIRECTION, REED7_HOMING_X, STP_Y_PULSE, STP_Y_DIRECTION, REED6_HOMING_Y, STP_Z_PULSE, STP_Z_DIRECTION, REED8_HOMING_Z, claw);
	this->rotaryEncoder = RotaryEncoder(S4_ROTARY_ENCODER_CLK, S4_ROTARY_ENCODER_DT);
	this->loadCell.begin(HX1_LOAD_CELL_DT, HX1_LOAD_CELL_SCK);
	this->loadCell.set_scale(loadCellDivider);
	this->loadCell.set_offset(loadCellOffset);
}

Machine::Machine(vector<vector<WaterBalloon>> waterBalloonPositions) : Machine()
{
	this->grid = Grid(waterBalloonPositions);
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
	switch (value)
	{
		case 1:
			this->SetMode(new ClawManualPlacedWaterBalloonMode());
			break;
		case 2:
			this->SetMode(new QuicknessMode());
			break;
		case 3:
			this->SetMode(new GrabWaterBalloonMode());
			break;
		case 4:
			this->SetMode(new PlaceWaterballoonOnConveyorBeltMode());
			break;
		case 5:
			this->SetMode(new SortingMode());
			break;
		case 0:
		default:
			this->SetMode(new DefaultMode());
			break;
	}
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
	// Empty = 0
	// Small = 1
	// Medium = 2
	// Large = 3
	// Unkown = 4
	int sortingArea = 0;
	int speed = 50;
	int distance = 0;
	this->conveyorBelt.GetDCMotor().SetSpeed(speed);
	this->carriage.GetDCMotor().SetSpeed(speed);

	switch (this->conveyorBelt.GetState()->GetStateTypes()[this->conveyorBelt.GetState()->ToString()])
	{
		case StateType::NoneRowEmptyStateType:
			sortingArea = this->GetConveyorBelt().GetFirstRowType();
			break;		
		case StateType::FirstRowEmptyStateType:
			sortingArea = this->GetConveyorBelt().GetSecondRowType();
			break;
		case StateType::SecondRowEmptyStateType:
			sortingArea = this->GetConveyorBelt().GetThirdRowType();
			break;
		case StateType::BaseGridStateType:
		case StateType::ThirdRowEmptyStateType:
		default:
			sortingArea = 0;
			break;
	}

	while (distance > 0)
	{
		distance--;

		// Adjust height of the carriage based on the int-value.
		// 1 = Bottom area, 2 = Middle area, 3 = Top area.
		switch (sortingArea)
		{
			case WaterBalloonType::Small:
				this->carriage.HandleDCMotor(speed, HALL_CARRIAGE_BOTTOM);
				break;
			case WaterBalloonType::Medium:
				this->carriage.HandleDCMotor(speed, HALL_CARRIAGE_MIDDLE);
				break;
			case WaterBalloonType::Large:
				this->carriage.HandleDCMotor(speed, HALL_CARRIAGE_TOP);
				break;		
			case WaterBalloonType::Empty:
			case WaterBalloonType::Unkown:
			default:
				break;
		}
	}

	this->conveyorBelt.HandleDCMotor();
	this->conveyorBelt.GetState()->Next(&this->conveyorBelt);	
}

void Machine::WeighWaterBalloon()
{
	float weight = 0;

	//weight = this->currentWaterBalloon.GetWeight();
	weight = this->loadCell.get_units(10);
	
	if (weight >= 0.8)
	{
		this->currentWaterBalloon.SetWeight(weight);

		if (this->conveyorBelt.CanAddWaterBalloon(this->currentWaterBalloon))
		{
			this->conveyorBelt.AddWaterBalloon(this->currentWaterBalloon);
			this->grid.SelectNextPosition();
		}
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
	this->robotArm.HandleArm(x, y, z);
}

void Machine::HomingRobotArm(int homeWhat)
{
	switch (homeWhat)
	{
		case 1:
			this->robotArm.Homing();
			break;
		case 2:
			this->robotArm.GetClaw().Homing();
			break;
		case 0:
		default:
			this->robotArm.HomingWithClaw();
			break;
	}
	
}

void Machine::TurnOnFrameMotor(DirectionType direction)
{
	this->frame.GetDCMotor().Start(direction);
}

void Machine::TurnOffFrameMotor()
{
	this->frame.GetDCMotor().Stop();
}

void Machine::TurnOnCarriageMotor(DirectionType direction)
{
	this->carriage.GetDCMotor().Start(direction);
}

void Machine::TurnOffCarriageMotor()
{
	this->carriage.GetDCMotor().Stop();
}

void Machine::TurnOnConveyorBeltMotor(DirectionType direction)
{
	this->conveyorBelt.GetDCMotor().Start(direction);
}

void Machine::TurnOffConveyorBeltMotor()
{
	this->conveyorBelt.GetDCMotor().Stop();
}

BaseMachineState* Machine::GetState()
{
	return this->state;
}

void Machine::SetState(BaseMachineState* value)
{
	this->state = value;
	this->controlPanel.Print(this->GetState()->ToString(), this->GetMode()->ToString());
}

BaseMode* Machine::GetMode()
{
	return this->mode;
}

void Machine::SetMode(BaseMode* value)
{
	this->mode = value;
	this->controlPanel.Print(this->GetState()->ToString(), this->GetMode()->ToString());
}

Grid Machine::GetGrid()
{
	return this->grid;
}

void Machine::SetGrid(Grid value)
{
	this->grid = value;
}

ConveyorBelt Machine::GetConveyorBelt()
{
	return this->conveyorBelt;
}

void Machine::SetConveyorBelt(ConveyorBelt value)
{
	this->conveyorBelt = value;

}

RotaryEncoder Machine::GetRotaryEncoder()
{
	return this->rotaryEncoder;
}

WaterBalloon Machine::GetCurrentWaterBalloon()
{
	return this->currentWaterBalloon;
}

void Machine::SetCurrentWaterBalloon(WaterBalloon value)
{
	this->currentWaterBalloon = value;
}

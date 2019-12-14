#pragma once
#include "TominatorPins.h"
#define DEBUG false
#define STEPS_PER_REVOLUTION 2000

#define BASE_GRID_STATE "BaseGridState"
#define NONE_ROW_EMPTY_STATE "NoneRowEmptyState"
#define FIRST_ROW_EMPTY_STATE "FirstRowEmptyState"
#define SECOND_ROW_EMPTY_STATE "SecondRowEmptyState"
#define THIRD_ROW_EMPTY_STATE "ThirdRowEmptyState"

#define BASE_MACHINE_STATE "BaseMachineState"
#define BOOT_UP_STATE "BootUpState"
#define STANDBY_STATE "StandbyState"
#define INITIALIZE_STATE "InitializeState"
#define RUNNING_STATE "RunningState"

#define BASE_MODE "BaseModeState"
#define MODE0 "DefaultMode"
#define MODE1 "ClawManualPlacedWaterBalloonMode"
#define MODE2 "QuicknessMode"
#define MODE3 "GrabWaterBalloonMode"
#define MODE4 "PutWaterballoonOnConveyorBelt"
#define MODE5 "SortingMode"

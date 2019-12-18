#pragma once
#include "TominatorPins.h"

#define DEBUG false
#define STEPS_PER_REVOLUTION 2000


// All states and modes mainly useful for comparisons or debug purposes, such as showing on screen in what state/mode the machine resides in
#define BASE_GRID_STATE "BaseGridState"
#define NONE_ROW_EMPTY_STATE "None Row Empty"
#define FIRST_ROW_EMPTY_STATE "First Row Empty"
#define SECOND_ROW_EMPTY_STATE "Second Row Empty"
#define THIRD_ROW_EMPTY_STATE "Third Row Empty"

#define BASE_MACHINE_STATE "BaseMachineState"
#define BOOT_UP_STATE "Boot Up"
#define STANDBY_STATE "Standby"
#define INITIALIZE_STATE "Initialize"
#define RUNNING_STATE "Running"

#define BASE_MODE "BaseMode"
#define MODE0 "MODE0"
#define MODE1 "MODE1"
#define MODE2 "MODE2"
#define MODE3 "MODE3"
#define MODE4 "MODE4"
#define MODE5 "MODE5"
#define MODE6 "MODE6"
#define MODE7 "MODE7"

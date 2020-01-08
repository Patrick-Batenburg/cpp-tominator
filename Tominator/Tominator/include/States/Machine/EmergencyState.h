#pragma once
#include "BaseMachineState.h"

class EmergencyState : public BaseMachineState
{
public:
	/**
		Initializes a new instance of the EmergencyState class.
	*/
	EmergencyState();

	/**
		Deconstruct the instance of the EmergencyState class.
	*/
	~EmergencyState();

	/**
		Provides the Machine with a new running state.
	*/
	virtual void Reset(Machine* machine);

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current state.
	*/
	virtual String ToString();
};

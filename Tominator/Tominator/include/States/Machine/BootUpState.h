#pragma once
#include "BaseMachineState.h"

class BootUpState : public BaseMachineState
{
public:
	/**
		Initializes a new instance of the BootUpState class.
	*/
	BootUpState();

	/**
		Deconstruct the instance of the BootUpState class.
	*/
	~BootUpState();

	/**
		Provides the Machine with a new standby state.
	*/
	virtual void Reset(Machine* machine);

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current state.
	*/
	virtual std::string ToString();
};

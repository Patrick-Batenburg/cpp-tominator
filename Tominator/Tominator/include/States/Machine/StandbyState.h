#pragma once
#include "BaseMachineState.h"

class StandbyState : public BaseMachineState
{
public:
	/**
		Initializes a new instance of the StandbyState class.
	*/
	StandbyState();

	/**
		Deconstruct the instance of the StandbyState class.
	*/
	~StandbyState();

	/**
		Provides the Machine with a new initialize state.
	*/
	virtual void Start(Machine* machine);

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current state.
	*/
	virtual String ToString();
};

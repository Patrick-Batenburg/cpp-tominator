#pragma once
#include "BaseMachineState.h"

class InitializeState : public BaseMachineState
{
public:
	/**
		Initializes a new instance of the InitializeState class.
	*/
	InitializeState();

	/**
		Deconstruct the instance of the InitializeState class.
	*/
	~InitializeState();

	/**
		Provides the Machine with a new running state.
	*/
	virtual void Start(Machine* machine);

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current state.
	*/
	virtual std::string ToString();

};

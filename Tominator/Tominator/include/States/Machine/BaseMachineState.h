#pragma once
#include "TominatorVariables.h"
#include <string>

class Machine; // forward declaration

class BaseMachineState
{
public:
	/**
		Initializes a new instance of the BaseMachineState class.
	*/
	BaseMachineState();

	/**
		Deconstruct the instance of the BaseMachineState class.
	*/
	~BaseMachineState();

	/**
		Provides the Machine with a new state.
	*/
	virtual void Start(Machine* machine);

	/**
		Provides the Machine with a new state.
	*/
	virtual void Reset(Machine* machine);

	/**
		Provides the Machine with a new boot up state.
	*/
	virtual void EmergencyStop(Machine* machine);

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
	
		@return A string that represents the current state.
	*/
	virtual std::string ToString();
};

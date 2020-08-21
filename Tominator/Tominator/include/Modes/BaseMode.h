#pragma once
#include "TominatorVariables.h"
#include <WString.h>

class Machine; // forward declaration
class BaseMachineState; // forward declaration

class BaseMode
{
public:
	/**
		Initializes a new instance of the BaseMode class.
	*/
	BaseMode();

	/**
		Deconstruct the instance of the BaseMode class.
	*/
	~BaseMode();
	
	virtual void Initialize(Machine* machine);

	/**
		Provides the Machine with a set of instructions.
	*/
	void Execute(Machine* machine);

	/**
		Returns a string that represents the current mode.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current mode.
	*/
	virtual String ToString();

private:
	/**
		Allows an interface for defining a set of instructions/operations (modes) on the machine.
	*/
	virtual void HandlePlaceholder(Machine* machine) = 0;
};

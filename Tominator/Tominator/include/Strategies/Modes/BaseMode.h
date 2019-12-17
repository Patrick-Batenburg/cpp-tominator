#pragma once
#include "TominatorVariables.h"
#include <string>

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

	/**
		Provides the Machine with a set of instructions.
	*/
	void Execute(Machine* machine);

	/**
		Returns a string that represents the current mode.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current mode.
	*/
	virtual std::string ToString();

private:
	/**
		Allows an interface for defining a set of instructions/operations (modes) on the machine.
	*/
	virtual void HandlePlaceholder(Machine* machine) = 0;
};

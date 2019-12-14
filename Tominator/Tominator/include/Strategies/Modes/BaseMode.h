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
		Returns a string that represents the current object class name.
		
		@return A string that represents the current object class name.
	*/
	virtual std::string ToString();
private:
	/**
		Defines a set of instructions.
	*/
	virtual void HandlePlaceholder(Machine* machine) = 0;
};

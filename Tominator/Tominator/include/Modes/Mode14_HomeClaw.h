#pragma once
#include "BaseMode.h"

class HomeClawMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the HomeClawMode class.
	*/
	HomeClawMode();

	/**
		Deconstruct the instance of the HomeClawMode class.
	*/
	~HomeClawMode();

	/**
		Returns a string that represents the current mode.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current mode.
	*/
	virtual String ToString();

private:
	/**
		Defines a set of instructions.
	*/
	virtual void HandlePlaceholder(Machine* machine);
};


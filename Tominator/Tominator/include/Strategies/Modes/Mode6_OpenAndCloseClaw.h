#pragma once
#include "BaseMode.h"

class OpenAndCloseClawMode : public BaseMode
{
	/**
		Initializes a new instance of the OpenAndCloseClawMode class.
	*/
	OpenAndCloseClawMode();

	/**
		Deconstruct the instance of the OpenAndCloseClawMode class.
	*/
	~OpenAndCloseClawMode();

	/**
		Returns a string that represents the current mode.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current mode.
	*/
	virtual std::string ToString();

private:
	/**
		Defines a set of instructions.
	*/
	virtual void HandlePlaceholder(Machine* machine);
};

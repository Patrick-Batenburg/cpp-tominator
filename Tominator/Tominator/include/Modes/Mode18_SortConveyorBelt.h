#pragma once
#include "BaseMode.h"

class SortConveyorBeltMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the SortConveyorBeltMode class.
	*/
	SortConveyorBeltMode();

	/**
		Deconstruct the instance of the SortConveyorBeltMode class.
	*/
	~SortConveyorBeltMode();

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
#pragma once
#include "BaseMode.h"

class ClawSortingMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the SortingMode class.
	*/
	ClawSortingMode();

	/**
		Deconstruct the instance of the SortingMode class.
	*/
	~ClawSortingMode();
	
	void Initialize(Machine* machine);

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

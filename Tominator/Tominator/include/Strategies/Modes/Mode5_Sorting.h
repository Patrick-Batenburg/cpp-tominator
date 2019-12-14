#pragma once
#include "BaseMode.h"

class SortingMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the SortingMode class.
	*/
	SortingMode();

	/**
		Deconstruct the instance of the SortingMode class.
	*/
	~SortingMode();

	/**
		Returns a string that represents the current object class name.
		
		@return A string that represents the current object class name.
	*/
	virtual std::string ToString();
private:
	/**
		Defines a set of instructions.
	*/
	virtual void HandlePlaceholder(Machine* machine);
};

#pragma once
#include "BaseMode.h"

class DefaultMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the DefaultMode class.
	*/
	DefaultMode();

	/**
		Deconstruct the instance of the DefaultMode class.
	*/
	~DefaultMode();

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

#pragma once
#include "BaseMode.h"
#include "WaterBalloon.h"

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

#pragma once
#include "BaseMode.h"

class CarriageBeyondTopSensorMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the CarriageBeyondTopSensorMode class.
	*/
	CarriageBeyondTopSensorMode();

	/**
		Deconstruct the instance of the CarriageBeyondTopSensorMode class.
	*/
	~CarriageBeyondTopSensorMode();
	
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

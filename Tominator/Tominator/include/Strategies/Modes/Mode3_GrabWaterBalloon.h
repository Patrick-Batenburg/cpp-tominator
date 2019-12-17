#pragma once
#include "BaseMode.h"

class GrabWaterBalloonMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the GrabWaterBalloonMode class.
	*/
	GrabWaterBalloonMode();

	/**
		Deconstruct the instance of the GrabWaterBalloonMode class.
	*/
	~GrabWaterBalloonMode();

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

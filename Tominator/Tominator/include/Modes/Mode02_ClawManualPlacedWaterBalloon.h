#pragma once
#include "BaseMode.h"

class ClawManualPlacedWaterBalloonMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the ClawManualPlacedWaterBalloonMode class.
	*/
	ClawManualPlacedWaterBalloonMode();

	/**
		Deconstruct the instance of the ClawManualPlacedWaterBalloonMode class.
	*/
	~ClawManualPlacedWaterBalloonMode();
	
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

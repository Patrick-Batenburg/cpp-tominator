#pragma once
#include "BaseMode.h"

class PlaceWaterballoonOnConveyorBeltMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the PlaceWaterballoonOnConveyorBeltMode class.
	*/
	PlaceWaterballoonOnConveyorBeltMode();

	/**
		Deconstruct the instance of the PlaceWaterballoonOnConveyorBeltMode class.
	*/
	~PlaceWaterballoonOnConveyorBeltMode();

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

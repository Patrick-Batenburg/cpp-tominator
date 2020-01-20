#pragma once
#include "BaseMode.h"
#include "WaterBalloon.h"
#include "Grid.h"
#include "Machine.h"

class SerialPrintSimulationMode : public BaseMode
{	
public:
	/**
		Initializes a new instance of the SerialPrintSimulationMode class.
	*/
	SerialPrintSimulationMode();

	/**
		Deconstruct the instance of the SerialPrintSimulationMode class.
	*/
	~SerialPrintSimulationMode();

	/**
		A helper function for printing water balloons. Returns a string that represents a water balloon. 
		
		@return A string that represents a water balloon.
	*/
	String ToString(WaterBalloonType value);

	/**
		Returns a string that represents the current mode.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current mode.
	*/
	virtual String ToString();

	friend class Machine;
private:	
	/**
		Defines a set of instructions.
	*/
	virtual void HandlePlaceholder(Machine* machine);
};

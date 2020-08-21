#pragma once
#include "BaseMode.h"

class ZAxisUpAndDownMode : public BaseMode
{
public:
	/**
		Initializes a new instance of the ZAxisUpAndDownMode class.
	*/
	ZAxisUpAndDownMode();

	/**
		Deconstruct the instance of the ZAxisUpAndDownMode class.
	*/
	~ZAxisUpAndDownMode();
	
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

#pragma once
#include "BaseGridState.h"

class SecondRowEmptyState : public BaseGridState
{
public:
	/**
		Initializes a new instance of the SecondRowEmptyState class.
	*/
	SecondRowEmptyState();

	/**
		Deconstruct the instance of the SecondRowEmptyState class.
	*/
	~SecondRowEmptyState();	

	/**
		Provides the BaseGrid with a new state.
	*/
	virtual void Next(BaseGrid* baseGrid);	

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current state.
	*/
	virtual String ToString();
};

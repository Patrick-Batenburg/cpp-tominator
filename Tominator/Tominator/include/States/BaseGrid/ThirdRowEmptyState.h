#pragma once
#include "BaseGridState.h"

class ThirdRowEmptyState : public BaseGridState
{
public:
	/**
		Initializes a new instance of the ThirdRowEmptyState class.
	*/
	ThirdRowEmptyState();

	/**
		Deconstruct the instance of the ThirdRowEmptyState class.
	*/
	~ThirdRowEmptyState();

	/**
		Provides the BaseGrid with a new state.
	*/
	virtual void Next(BaseGrid* baseGrid);

	/**
		Returns a string that represents the current object class name.
		
		@return A string that represents the current object class name.
	*/
	virtual std::string ToString();
};

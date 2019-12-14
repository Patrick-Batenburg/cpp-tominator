#pragma once
#include "BaseGridState.h"

class NoneRowEmptyState : public BaseGridState
{
public:
	/**
		Initializes a new instance of the NoneRowEmptyState class.
	*/
	NoneRowEmptyState();

	/**
		Deconstruct the instance of the NoneRowEmptyState class.
	*/
	~NoneRowEmptyState();

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

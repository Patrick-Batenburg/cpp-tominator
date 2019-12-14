#pragma once
#include "BaseGridState.h"

class FirstRowEmptyState : public BaseGridState
{
public:
	/**
		Initializes a new instance of the FirstRowEmptyState class.
	*/
	FirstRowEmptyState();

	/**
		Deconstruct the instance of the FirstRowEmptyState class.
	*/
	~FirstRowEmptyState();

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

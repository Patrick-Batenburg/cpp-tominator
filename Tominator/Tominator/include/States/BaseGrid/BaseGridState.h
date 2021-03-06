#pragma once
#include "TominatorVariables.h"
#include <map>
#include <WString.h>

enum BaseGridStateType
{
	BaseGridType,
	NoneRowEmptyStateType,
	FirstRowEmptyStateType,
	SecondRowEmptyStateType,
	ThirdRowEmptyStateType
};

class BaseGrid; // forward declaration

class BaseGridState
{
private:
	std::map<String, BaseGridStateType> stateTypes;

public:
	/**
		Initializes a new instance of the BaseGridState class.
	*/
	BaseGridState();

	/**
		Deconstruct the instance of the BaseGridState class.
	*/
	~BaseGridState();	

	/**
		Provides the BaseGrid with a new state.
	*/
	virtual void Next(BaseGrid* baseGrid);	

	/**
		Gets the different grid states for making comparisons.
		
		@return All the different grid states.
	*/
	std::map<String, BaseGridStateType> GetStateTypes();

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current state.
	*/
	virtual String ToString();
};

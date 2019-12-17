#pragma once
#include "TominatorVariables.h"
#include <string>
#include <map>

enum StateType
{
	BaseGridStateType,
	NoneRowEmptyStateType,
	FirstRowEmptyStateType,
	SecondRowEmptyStateType,
	ThirdRowEmptyStateType
};

class BaseGrid; // forward declaration

class BaseGridState
{
private:
	std::map<std::string, StateType> stateTypes;

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
	std::map<std::string, StateType> GetStateTypes();

	/**
		Returns a string that represents the current state.
		Only useful for comparisons and debug purposes.
		
		@return A string that represents the current state.
	*/
	virtual std::string ToString();
};

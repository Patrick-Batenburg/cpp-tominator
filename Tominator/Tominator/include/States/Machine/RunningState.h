#pragma once
#include "BaseMachineState.h"

class RunningState : public BaseMachineState
{
public:
	/**
		Initializes a new instance of the RunningState class.
	*/
	RunningState();

	/**
		Deconstruct the instance of the RunningState class.
	*/
	~RunningState();

	/**
		Returns a string that represents the current object class name.
		
		@return A string that represents the current object class name.
	*/
	virtual std::string ToString();
};

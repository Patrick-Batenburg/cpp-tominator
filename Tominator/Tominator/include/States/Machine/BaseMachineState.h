#pragma once
#include "TominatorVariables.h"
#include <map>
#include <WString.h>

enum BaseMachineStateType
{
	BaseMachineType,
	BootUpStateType,
	StandbyStateType,
	InitializeStateType,
	RunningStateType,
	EmergencyStateType
};

class Machine; // forward declaration

class BaseMachineState
{
private:
	bool isFinished;
	std::map<String, BaseMachineStateType> stateTypes;

public:
	/**
		Initializes a new instance of the BaseMachineState class.
	*/
	BaseMachineState();

	/**
		Deconstruct the instance of the BaseMachineState class.
	*/
	~BaseMachineState();

	/**
		Provides the Machine with a new state.
	*/
	virtual void Start(Machine* machine);

	/**
		Provides the Machine with a new state.
	*/
	virtual void Reset(Machine* machine);

	/**
		Provides the Machine with a new boot up state.
	*/
	virtual void EmergencyStop(Machine* machine);

	bool IsFinished();
	void Finished();

	/**
		Gets the different grid states for making comparisons.
		
		@return All the different grid states.
	*/
	std::map<String, BaseMachineStateType> GetStateTypes();

	/**
		Returns a String that represents the current state.
		Only useful for comparisons and debug purposes.
	
		@return A String that represents the current state.
	*/
	virtual String ToString();
};

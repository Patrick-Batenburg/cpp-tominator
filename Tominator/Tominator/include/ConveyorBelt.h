#pragma once
#include "BaseGrid.h"
#include "DCMotor.h"

class ConveyorBelt : public BaseGrid
{
private:
	enum WaterBalloonType firstRowType;
	enum WaterBalloonType secondRowType;
	enum WaterBalloonType thirdRowType;
	int transportedWaterBalloons;
	int transportedWaterBalloonsGoal;
	int reedPin;
	DCMotor dcMotor; 

public:
	/**
		Initializes a new instance of the ConveyorBelt class.
	*/
	ConveyorBelt();

	/**
		Initializes a new instance of the ConveyorBelt class.
		
		@param dcMotor	The DCMotor object.
		@param reedPin	The reed contact located under the wall strip.
	*/
	ConveyorBelt(DCMotor dcMotor, int reedPin);

	/**
		Deconstruct the instance of the ConveyorBelt class.
	*/
	~ConveyorBelt();

	/**
		Determines whenever or not the specified water balloon can be put onto the conveyor belt.
		
		@return True if the water balloon can be put onto the conveyor belt, otherwise false.
	*/
	bool CanAddWaterBalloon(WaterBalloon waterBalloon);

	/**
		Adds the specified water balloon to the 2D matrix.
	*/
	void AddWaterBalloon(WaterBalloon waterBalloon);

	/**
		Handles the DC motor. The DC motor can only run when sufficient water balloons are transported. See GetTransportedWaterBalloonsGoal().
	*/
	void HandleDCMotor();

	/**
		Gets the water balloon type of the first row.
		
		@return The water balloon type of the first row.
	*/
	WaterBalloonType GetFirstRowType();

	/**
		Sets the water balloon type of the first row.
		
		@param value The new water balloon type.
	*/
	void SetFirstRowType(WaterBalloonType value);

	/**
		Gets the water balloon type of the second row.
		
		@return The water balloon type of the second row.
	*/
	WaterBalloonType GetSecondRowType();

	/**
		Sets the water balloon type of the second row.
		
		@param value The new water balloon type.
	*/
	void SetSecondRowType(WaterBalloonType value);

	/**
		Gets the water balloon type of the third row.
		
		@return The water balloon type of the third row.
	*/
	WaterBalloonType GetThirdRowType();

	/**
		Sets the water balloon type of the third row.
		
		@param value The new water balloon type.
	*/
	void SetThirdRowType(WaterBalloonType value);

	/**
		Gets the current amount of transported water balloons.
		
		@return The current amount of transported water balloons.
	*/
	int GetTransportedWaterBalloons();

	/**
		Gets the goal of transported water balloons needed.
		
		@return The goal of transported water balloons needed.
	*/
	int GetTransportedWaterBalloonsGoal();

	/**
		Sets the goal of transported water balloons needed.
		
		@param value The new goal.
	*/
	void SetTransportedWaterBalloonsGoal(int value);

	/**
		Sets the goal of transported water balloons needed.
		
		@param value The new state.
	*/
	virtual void SetState(BaseGridState* value);

	/**
		Gets the DC motor object.
		
		@return The DC motor object.
	*/
	DCMotor GetDCMotor();
	
private:
	/**
		Sets the current amount of transported water balloons.
		
		@param value The new current amount of transported water balloons.
	*/
	void SetTransportedWaterBalloons(int value);

	/**
		Increments the current amount of transported water balloons by 1.
	*/
	void IncrementTransportedWaterBalloons();
};

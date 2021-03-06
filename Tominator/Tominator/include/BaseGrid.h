#pragma once
#include "WaterBalloon.h"
#include "BaseGridState.h"
#include <vector>

class BaseGrid
{
private:
	int currentRow;
	int currentColumn;

protected:
	std::vector<std::vector<WaterBalloon>> waterBalloonPositions;
	BaseGridState* state;

public:
	/**
		Initializes a new instance of the BaseGrid class.
	*/
	BaseGrid();
	
	/**
		Initializes a new instance of the BaseGrid class.
		
		@param type The type of water balloons to fill the 2D matrix with.
	*/
	BaseGrid(WaterBalloonType type);

	/**
		Deconstruct the instance of the BaseGrid class.
	*/
	~BaseGrid();
	
	/**
		Clears the 2D matrix to it's default values.
	*/
	virtual void Reset();

	/**
		Gets the current selected row.
		
		@return The current selected row.
	*/
	int GetCurrentRow();

	/**
		Sets the current selected row.
		
		@param value The selected row.
	*/
	void SetCurrentRow(int value);

	/**
		Gets the current selected column.
		
		@return The current selected column.
	*/
	int GetCurrentColumn();
	
	/**
		Sets the current selected column.
		
		@param value The selected column.
	*/
	void SetCurrentColumn(int value);

	/**
		Gets the state.
		
		@return The state.
	*/
	BaseGridState* GetState();

	/**
		Sets the state.
		
		@param value The new state.
	*/
	virtual void SetState(BaseGridState* value);
	
	/**
		Gets the water balloon positions.

		@return The water balloon positions in a 2D matrix (3x3) representation.
	*/
	std::vector<std::vector<WaterBalloon>> GetWaterBalloonPositions();

	/**
		Sets the water balloon positions.
		
		@param value The new water balloon positions.
	*/
	void SetWaterBalloonPositions(std::vector<std::vector<WaterBalloon>> value);
};

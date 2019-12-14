#pragma once
#include "BaseGrid.h"

class Grid : public BaseGrid
{	
public:
	/**
		Initializes a new instance of the Grid class.
	*/
	Grid();

	/**
		Initializes a new instance of the Grid class.
		
		@param waterBalloonPositions The water balloon positions in a 2D matrix to use. Can have predetermined weights for testing purposes.
	*/
	Grid(std::vector<std::vector<WaterBalloon>> waterBalloonPositions);
	
	/**
		Deconstruct the instance of the Grid class.
	*/
	~Grid();

	/**
		Updates the selected row and column.
	*/
	void MoveToNextSection();
};

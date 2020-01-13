#include "Grid.h"

using namespace std;

Grid::Grid() : BaseGrid(WaterBalloonType::Unkown)
{
}

Grid::Grid(vector<vector<WaterBalloon>> waterBalloonPositions) : Grid()
{
	this->waterBalloonPositions.clear();
	this->waterBalloonPositions = waterBalloonPositions;
}

Grid::~Grid()
{
}

void Grid::SelectNextPosition()
{
	this->waterBalloonPositions[this->GetCurrentRow()][this->GetCurrentColumn()].SetType(WaterBalloonType::Empty);

	if (this->GetCurrentColumn() == 2)
	{
		if (this->GetCurrentRow() == 2)
		{
			this->GetState()->Next(this);
			this->SetCurrentRow(0);
		}
		else
		{
			this->SetCurrentRow(this->GetCurrentRow() + 1);
		}

		this->SetCurrentColumn(0);
	}
	else
	{
		this->SetCurrentColumn(this->GetCurrentColumn() + 1);
	}
}

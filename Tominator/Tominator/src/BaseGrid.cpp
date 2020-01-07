#include "BaseGrid.h"
#include "NoneRowEmptyState.h"

using namespace std;

BaseGrid::BaseGrid()
{
	this->waterBalloonPositions = vector<vector<WaterBalloon>>(3, vector<WaterBalloon>(3, WaterBalloon()));
	this->currentRow = 0;
	this->currentColumn = 0;
	this->state = new NoneRowEmptyState();
	this->selectedCell.Row = this->currentRow;
	this->selectedCell.Column = this->currentColumn;
	this->selectedCell.InitialType = WaterBalloonType::Empty;
}

BaseGrid::BaseGrid(WaterBalloonType type) : BaseGrid()
{
	this->waterBalloonPositions = vector<vector<WaterBalloon>>(3, vector<WaterBalloon>(3, WaterBalloon(type)));
	this->selectedCell.InitialType = type;
}

BaseGrid::~BaseGrid()
{
}

void BaseGrid::Clear()
{
	this->waterBalloonPositions = vector<vector<WaterBalloon>>(3, vector<WaterBalloon>(3, WaterBalloon(this->selectedCell.InitialType)));
}

Cell BaseGrid::GetNearestUnusedCell(bool reiterating)
{
	if (reiterating)
	{
		for (int i = 0; i < this->GetWaterBalloonPositions().size(); i++)
		{
			for (int j = 0; j < this->GetWaterBalloonPositions()[i].size(); j++)
			{
				if (this->GetWaterBalloonPositions()[i][j].GetType() == this->selectedCell.InitialType)
				{
					this->selectedCell.Row = i;
					this->selectedCell.Column = j;
				}
			}
		}
	}
	else
	{
		for (int i = this->selectedCell.Row; i < this->GetWaterBalloonPositions().size(); i++)
		{
			for (int j = this->selectedCell.Column; j < this->GetWaterBalloonPositions()[i].size(); j++)
			{
				if (this->GetWaterBalloonPositions()[i][j].GetType() == this->selectedCell.InitialType)
				{
					this->selectedCell.Row = i;
					this->selectedCell.Column = j;
				}
			}
		}
	}
	
	return this->selectedCell;
}

int BaseGrid::GetCurrentRow()
{
	return this->currentRow;
}

void BaseGrid::SetCurrentRow(int value)
{
	this->currentRow = value;
}

int BaseGrid::GetCurrentColumn()
{
	return this->currentColumn;
}

void BaseGrid::SetCurrentColumn(int value)
{
	this->currentColumn = value;
}

BaseGridState* BaseGrid::GetState()
{
	return this->state;
}

void BaseGrid::SetState(BaseGridState* value)
{
	this->state = value;
}

vector<vector<WaterBalloon>> BaseGrid::GetWaterBalloonPositions()
{
	return this->waterBalloonPositions;
}

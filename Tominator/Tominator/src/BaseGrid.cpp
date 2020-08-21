#include "BaseGrid.h"
#include "NoneRowEmptyState.h"

using namespace std;

BaseGrid::BaseGrid()
{
	this->waterBalloonPositions = vector<vector<WaterBalloon>>(3, vector<WaterBalloon>(3, WaterBalloon()));
	this->currentRow = 0;
	this->currentColumn = 0;
	this->state = new NoneRowEmptyState();
}

BaseGrid::BaseGrid(WaterBalloonType type) : BaseGrid()
{
	this->waterBalloonPositions.clear();
	this->waterBalloonPositions = vector<vector<WaterBalloon>>(3, vector<WaterBalloon>(3, WaterBalloon(type)));
}

BaseGrid::~BaseGrid()
{
}

void BaseGrid::Reset()
{
	this->waterBalloonPositions.clear();
	this->waterBalloonPositions = vector<vector<WaterBalloon>>(3, vector<WaterBalloon>(3, WaterBalloon()));
	this->SetState(new NoneRowEmptyState());
	this->SetCurrentRow(0);
	this->SetCurrentColumn(0);
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
	delete this->state;
	this->state = value;
}

vector<vector<WaterBalloon>> BaseGrid::GetWaterBalloonPositions()
{
	return this->waterBalloonPositions;
}

void BaseGrid::SetWaterBalloonPositions(std::vector<std::vector<WaterBalloon>> value)
{
	this->waterBalloonPositions.clear();
	this->waterBalloonPositions = value;
}

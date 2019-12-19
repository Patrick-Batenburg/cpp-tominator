#include "BaseGridState.h"
#include "BaseGrid.h"

using namespace std;

BaseGridState::BaseGridState()
{	
	this->stateTypes[BASE_GRID_STATE] = BaseGridStateType::BaseGridType;
	this->stateTypes[NONE_ROW_EMPTY_STATE] = BaseGridStateType::NoneRowEmptyStateType;
	this->stateTypes[FIRST_ROW_EMPTY_STATE] = BaseGridStateType::FirstRowEmptyStateType;
	this->stateTypes[SECOND_ROW_EMPTY_STATE] = BaseGridStateType::SecondRowEmptyStateType;
	this->stateTypes[THIRD_ROW_EMPTY_STATE] = BaseGridStateType::ThirdRowEmptyStateType;
}

BaseGridState::~BaseGridState()
{
}

void BaseGridState::Next(BaseGrid* baseGrid)
{
	//baseGrid->SetState(this);
}

std::map<std::string, BaseGridStateType> BaseGridState::GetStateTypes()
{
	return this->stateTypes;
}

string BaseGridState::ToString()
{
	return BASE_GRID_STATE;
}
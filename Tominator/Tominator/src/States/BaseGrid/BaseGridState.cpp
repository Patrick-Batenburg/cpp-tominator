#include "BaseGridState.h"
#include "BaseGrid.h"

using namespace std;

BaseGridState::BaseGridState()
{	
	this->stateTypes[BASE_GRID_STATE] = StateType::BaseGridStateType;
	this->stateTypes[NONE_ROW_EMPTY_STATE] = StateType::NoneRowEmptyStateType;
	this->stateTypes[FIRST_ROW_EMPTY_STATE] = StateType::FirstRowEmptyStateType;
	this->stateTypes[SECOND_ROW_EMPTY_STATE] = StateType::SecondRowEmptyStateType;
	this->stateTypes[THIRD_ROW_EMPTY_STATE] = StateType::ThirdRowEmptyStateType;
}

BaseGridState::~BaseGridState()
{
}

void BaseGridState::Next(BaseGrid* baseGrid)
{
	//baseGrid->SetState(this);
}

std::map<std::string, StateType> BaseGridState::GetStateTypes()
{
	return this->stateTypes;
}

string BaseGridState::ToString()
{
	return BASE_GRID_STATE;
}
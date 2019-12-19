#include "FirstRowEmptyState.h"
#include "SecondRowEmptyState.h"
#include "BaseGrid.h"

FirstRowEmptyState::FirstRowEmptyState()
{
}

FirstRowEmptyState::~FirstRowEmptyState()
{
}

void FirstRowEmptyState::Next(BaseGrid* baseGrid)
{
	baseGrid->SetState(new SecondRowEmptyState());
}

String FirstRowEmptyState::ToString()
{
	return FIRST_ROW_EMPTY_STATE;
}

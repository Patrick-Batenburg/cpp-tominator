#include "FirstRowEmptyState.h"
#include "SecondRowEmptyState.h"
#include "BaseGrid.h"

using namespace std;

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

string FirstRowEmptyState::ToString()
{
	return FIRST_ROW_EMPTY_STATE;
}

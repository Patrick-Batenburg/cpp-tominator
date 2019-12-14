#include "SecondRowEmptyState.h"
#include "ThirdRowEmptyState.h"
#include "BaseGrid.h"

using namespace std;

SecondRowEmptyState::SecondRowEmptyState()
{
}

SecondRowEmptyState::~SecondRowEmptyState()
{
}

void SecondRowEmptyState::Next(BaseGrid* baseGrid)
{
	baseGrid->SetState(new ThirdRowEmptyState());
}

string SecondRowEmptyState::ToString()
{
	return SECOND_ROW_EMPTY_STATE;
}

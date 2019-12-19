#include "SecondRowEmptyState.h"
#include "ThirdRowEmptyState.h"
#include "BaseGrid.h"

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

String SecondRowEmptyState::ToString()
{
	return SECOND_ROW_EMPTY_STATE;
}

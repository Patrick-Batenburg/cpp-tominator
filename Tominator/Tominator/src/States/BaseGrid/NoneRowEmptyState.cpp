#include "NoneRowEmptyState.h"
#include "FirstRowEmptyState.h"
#include "BaseGrid.h"

NoneRowEmptyState::NoneRowEmptyState()
{
} 

NoneRowEmptyState::~NoneRowEmptyState()
{
}

void NoneRowEmptyState::Next(BaseGrid* baseGrid)
{
	baseGrid->SetState(new FirstRowEmptyState());
}

String NoneRowEmptyState::ToString()
{
	return NONE_ROW_EMPTY_STATE;
}
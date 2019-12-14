#include "NoneRowEmptyState.h"
#include "FirstRowEmptyState.h"
#include "BaseGrid.h"

using namespace std;

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

string NoneRowEmptyState::ToString()
{
	return NONE_ROW_EMPTY_STATE;
}
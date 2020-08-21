#include "Mode22_FrameSortingSideOffset.h"
#include "Machine.h"
#include "FirstRowEmptyState.h"
#include "NoneRowEmptyState.h"

FrameSortingSideOffsetMode::FrameSortingSideOffsetMode()
{
}

FrameSortingSideOffsetMode::~FrameSortingSideOffsetMode()
{
}

void FrameSortingSideOffsetMode::Initialize(Machine* machine)
{
	machine->GetGrid()->SetState(new NoneRowEmptyState());
}

void FrameSortingSideOffsetMode::HandlePlaceholder(Machine* machine)
{
	machine->GetGrid()->GetState()->Next(machine->GetGrid());
	Serial.println(machine->GetGrid()->GetState()->ToString());
	machine->GetFrame().HandleDCMotorOffset(true);
	delay(5000);
	machine->GetGrid()->GetState()->Next(machine->GetGrid());
	Serial.println(machine->GetGrid()->GetState()->ToString());
	machine->GetFrame().HandleDCMotorOffset(true);
	Serial.println("done");
}

String FrameSortingSideOffsetMode::ToString()
{
	return MODE22;
}

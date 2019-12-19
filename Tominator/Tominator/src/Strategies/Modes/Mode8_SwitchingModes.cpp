#include "Mode8_SwitchingModes.h"
#include "Machine.h"
#include "StandbyState.h"

using namespace std;

SwitchingModesMode::SwitchingModesMode()
{
}

SwitchingModesMode::~SwitchingModesMode()
{
}

void SwitchingModesMode::HandlePlaceholder(Machine* machine)
{
	machine->SetState(new StandbyState());

	for (;;)
	{
		if(Serial.available())
		{
			int inChar = Serial.parseInt();
			
			// Check if the number is not 8, as that would mean a new mode of the same type would be selected with another infinite for loop.
			if (inChar != 8)
			{
				machine->SelectMode(inChar);
			}
			else
			{
				// If it is equal, we simply break out of the loop.
				break;
			}
		}
	}
}

string SwitchingModesMode::ToString()
{
	return MODE8;
}

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder()
{
	this->counter = 0;
}

RotaryEncoder::RotaryEncoder(int clkPin, int dtPin) : RotaryEncoder()
{
	this->clkPin = clkPin;
	this->dtPin = dtPin;
	pinMode(clkPin, INPUT);
	pinMode(dtPin, INPUT);
}

RotaryEncoder::~RotaryEncoder()
{
}

void RotaryEncoder::CheckStateChange()
{
	byte output1 = digitalRead(clkPin);
	byte output2 = digitalRead(dtPin);
	byte newState = (output2 << 1) | output1;
	
	if (this->state != newState)
	{
		if ((this->state == 0 && newState == 2) || (this->state == 1 && newState == 0) || (this->state == 2 && newState == 3) || (this->state == 3 && newState == 1))
		{
			if (this->GetCounter() > 0)
			{
				counter--;
			}
		}
		else
		{
			counter++;
		}
		
		this->state = newState;
	}
}

int RotaryEncoder::GetCounter()
{
	CheckStateChange();
	return this->counter;
}

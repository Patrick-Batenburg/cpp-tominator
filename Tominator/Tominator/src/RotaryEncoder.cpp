#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder()
{
	this->counter = 0;
	this->currentStateCLK = 0;
	this->lastStateCLK = 0;
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

void RotaryEncoder::Update()
{
	// Read the current state of CLK
	currentStateCLK = digitalRead(clkPin);

	// If last and current state of CLK are different, then pulse occurred
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(dtPin) != currentStateCLK)
		{
			// Encoder is rotating CW so increment
			counter++;
		}
		else
		{
			counter--;
			
			if (this->counter < 0)
			{
				this->counter = 0;
			}
		}
	}

	// Remember last CLK state
	lastStateCLK = currentStateCLK;
}

int RotaryEncoder::GetCounter()
{
	//CheckStateChange();
	return this->counter;
}

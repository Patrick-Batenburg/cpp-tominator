#include "ControlPanel.h"
#include "Machine.h"
#include <pins_arduino.h>

ControlPanel::ControlPanel()
{
	pinMode(SDA, OUTPUT);
	pinMode(SCL, OUTPUT);
}

ControlPanel::ControlPanel(LiquidCrystal_I2C lcd, RotaryEncoder rotaryEncoder, EasyButton startButton, EasyButton resetButton, EasyButton emergencyStopButton)
{
	this->lcd = lcd;
	this->rotaryEncoder = rotaryEncoder;
	this->startButton = startButton;
	this->resetButton = resetButton;
	this->emergencyStopButton = emergencyStopButton;
}

ControlPanel::~ControlPanel()
{
} 

void ControlPanel::Print(String data1, String data2)
{
	lcd.clear();
	lcd.home();
	lcd.print(data1);
	
	if (data2 != "")
	{
		lcd.setCursor(0, 1);
		lcd.print(data2);
	}
}

EasyButton ControlPanel::GetStartButton()
{
	return this->startButton;
}

EasyButton ControlPanel::GetResetButton()
{
	return this->resetButton;
}

EasyButton ControlPanel::GetEmergencyStopButton()
{
	return this->emergencyStopButton;
}

RotaryEncoder ControlPanel::GetRotaryEncoder()
{
	return this->rotaryEncoder;
}

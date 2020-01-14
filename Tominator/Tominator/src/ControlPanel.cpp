#include "ControlPanel.h"
#include "Machine.h"
#include <pins_arduino.h>

ControlPanel::ControlPanel()
{
	pinMode(SDA, OUTPUT);
	pinMode(SCL, OUTPUT);
}

ControlPanel::ControlPanel(LiquidCrystal_I2C lcd, RotaryEncoder rotaryEncoder, EasyButton* startButton, EasyButton* resetButton, EasyButton* emergencyStopButton, JLed* startLed, JLed* resetLed)
{	
	this->lcd = lcd;
	this->rotaryEncoder = rotaryEncoder;
	this->startButton = startButton;
	this->resetButton = resetButton;
	this->emergencyStopButton = emergencyStopButton;
	this->startLed = startLed;
	this->resetLed = resetLed;
	this->ConfigureBootUpLed();
}

ControlPanel::~ControlPanel()
{
} 

void ControlPanel::Print(String data1, String data2)
{
	lcd.clear();
	lcd.home();
	
	if (data1 != "")
	{
		lcd.print(data1);
	}
	
	if (data2 != "")
	{
		lcd.setCursor(0, 1);
		lcd.print(data2);
	}
}

void ControlPanel::Clear()
{
	lcd.clear();
}

void ControlPanel::ReadButtons()
{
	this->startButton->read();
	this->resetButton->read();
	this->emergencyStopButton->read();
}

void ControlPanel::UpdateLeds()
{
	this->startLed->Update();
	this->resetLed->Update();
}

void ControlPanel::ConfigureStartLedOn()
{
	this->startLed->On();
}

void ControlPanel::ConfigureStartLedOff()
{
	this->startLed->Off();
}

void ControlPanel::ConfigureResetLedOn()
{
	this->resetLed->On();
}

void ControlPanel::ConfigureResetLedOff()
{
	this->resetLed->Off();
}

void ControlPanel::ConfigureBootUpLed()
{
	this->resetLed->Blink(2000, 1000);
	this->resetLed->Forever();
	this->ConfigureStartLedOff();
}

void ControlPanel::ConfigureStandbyLed()
{
	this->startLed->Blink(2000, 1000);
	this->startLed->Forever();
	this->resetLed->Blink(2000, 1000);
	this->resetLed->Forever();
}

void ControlPanel::ConfigureInitializeLed()
{
	this->startLed->Blink(300, 150);
	this->startLed->Forever();
	this->ConfigureResetLedOff();
}

void ControlPanel::ConfigureRunningLed()
{
	this->ConfigureStartLedOn();
	this->ConfigureResetLedOff();
}

void ControlPanel::ConfigureEmergencyLed()
{
	this->resetLed->Blink(300, 150);
	this->resetLed->Forever();
	this->ConfigureStartLedOff();
}

EasyButton* ControlPanel::GetStartButton()
{
	return this->startButton;
}

EasyButton* ControlPanel::GetResetButton()
{
	return this->resetButton;
}

EasyButton* ControlPanel::GetEmergencyStopButton()
{
	return this->emergencyStopButton;
}

RotaryEncoder ControlPanel::GetRotaryEncoder()
{
	return this->rotaryEncoder;
}

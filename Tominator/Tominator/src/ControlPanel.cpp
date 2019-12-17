#include "ControlPanel.h"
#include "Machine.h"
#include <pins_arduino.h>

using namespace std;

ControlPanel::ControlPanel()
{
}

ControlPanel::ControlPanel(int startButtonPin, int resetButtonPin, int emergencyStopButtonPin)
{
	this->startButtonPin = startButtonPin;
	this->resetButtonPin = resetButtonPin;
	this->emergencyStopButtonPin = emergencyStopButtonPin;
	pinMode(this->startButtonPin, INPUT);
	pinMode(this->resetButtonPin, INPUT);
	pinMode(this->emergencyStopButtonPin, INPUT);
	
	pinMode(SDA, OUTPUT);
	pinMode(SCL, OUTPUT);
	
	lcd.init();
	lcd.backlight();
}

//ControlPanel::ControlPanel(LiquidCrystal_I2C lcd, int startButtonPin, int resetButtonPin, int emergencyStopButtonPin) : ControlPanel(startButtonPin, resetButtonPin, emergencyStopButtonPin)
//{
	//this->lcd = lcd;
//}

ControlPanel::~ControlPanel()
{
} 

void ControlPanel::Print(string data1, string data2)
{
	lcd.clear();
	lcd.home();
	lcd.print(data1.c_str());
	
	if (data2 != "")
	{
		lcd.setCursor(0, 1);
		lcd.print(data2.c_str());
	}
}

int ControlPanel::GetStartButtonPin()
{
	return this->startButtonPin;
}

int ControlPanel::GetResetButtonPin()
{
	return this->resetButtonPin;
}

int ControlPanel::GetEmergencyStopButtonPin()
{
	return this->emergencyStopButtonPin;
}

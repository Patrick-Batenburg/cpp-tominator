#include "ControlPanel.h"
#include "Machine.h"
#include <pins_arduino.h>

ControlPanel::ControlPanel()
{
	pinMode(SDA, OUTPUT);
	pinMode(SCL, OUTPUT);
}

ControlPanel::ControlPanel(LiquidCrystal_I2C lcd) : ControlPanel()
{
	this->lcd = lcd;
	this->lcd.init();
	this->lcd.backlight();
}

ControlPanel::ControlPanel(LiquidCrystal_I2C lcd, RotaryEncoder rotaryEncoder, int startButtonPin, int resetButtonPin, int emergencyStopButtonPin) : ControlPanel(lcd)
{
	this->startButtonPin = startButtonPin;
	this->resetButtonPin = resetButtonPin;
	this->emergencyStopButtonPin = emergencyStopButtonPin;
	this->rotaryEncoder = rotaryEncoder;
	pinMode(this->startButtonPin, INPUT);
	pinMode(this->resetButtonPin, INPUT);
	pinMode(this->emergencyStopButtonPin, INPUT);	
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

void ControlPanel::TurnOnLED(int ledPin, bool blinking /*= true*/, int delayInMilliseconds /*= 1000*/)
{
	if (blinking)
	{
		digitalWrite(ledPin, HIGH);
		delay(delayInMilliseconds);
		digitalWrite(ledPin, LOW);
		delay(delayInMilliseconds);
	}
	else
	{
		digitalWrite(ledPin, HIGH);		
	}
}

void ControlPanel::TurnOffLED(int ledPin)
{
	digitalWrite(ledPin, LOW);
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

RotaryEncoder ControlPanel::GetRotaryEncoder()
{
	return this->rotaryEncoder;
}
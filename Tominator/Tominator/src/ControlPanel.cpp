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

ControlPanel::ControlPanel(LiquidCrystal_I2C lcd, int startButtonPin, int resetButtonPin, int emergencyStopButtonPin) : ControlPanel(lcd)
{
	this->startButtonPin = startButtonPin;
	this->resetButtonPin = resetButtonPin;
	this->emergencyStopButtonPin = emergencyStopButtonPin;
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

void ControlPanel::CheckButtonPress(Machine* machine)
{
	int buttonState = digitalRead(this->emergencyStopButtonPin);	

	if (buttonState == HIGH)
	{
		this->EmergencyStopButtonPressedEvent(machine);
	}
	
	buttonState = digitalRead(this->resetButtonPin);

	if (buttonState == HIGH)
	{
		this->ResetButtonPressedEvent(machine);
	}
	
	buttonState = digitalRead(this->startButtonPin);

	if (buttonState == HIGH)
	{
		this->StartButtonPressedEvent(machine);
	}
}

void ControlPanel::CheckButtonPress(Machine machine)
{
	int buttonState = digitalRead(this->emergencyStopButtonPin);

	if (buttonState == HIGH)
	{
		this->EmergencyStopButtonPressedEvent(machine);
	}
	
	buttonState = digitalRead(this->resetButtonPin);

	if (buttonState == HIGH)
	{
		this->ResetButtonPressedEvent(machine);
	}
	
	buttonState = digitalRead(this->startButtonPin);

	if (buttonState == HIGH)
	{
		this->StartButtonPressedEvent(machine);
	}
}

void ControlPanel::StartButtonPressedEvent(Machine* machine)
{
	machine->StartButtonPressed();
}

void ControlPanel::ResetButtonPressedEvent(Machine* machine)
{
	machine->ResetButtonPressed();
}

void ControlPanel::EmergencyStopButtonPressedEvent(Machine* machine)
{
	machine->EmergencyStopButtonPressed();
}

void ControlPanel::StartButtonPressedEvent(Machine machine)
{
	machine.StartButtonPressed();
}

void ControlPanel::ResetButtonPressedEvent(Machine machine)
{
	machine.ResetButtonPressed();
}

void ControlPanel::EmergencyStopButtonPressedEvent(Machine machine)
{
	machine.EmergencyStopButtonPressed();
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

#pragma once
#include <LiquidCrystal_I2C.h>
#include <string>

class Machine;
class ControlPanel
{
private:
	int startButtonPin;
	int resetButtonPin;
	int emergencyStopButtonPin;
	LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

public:
	/**
		Initializes a new instance of the ControlPanel class.
	*/
	ControlPanel();

	/**
		Initializes a new instance of the ControlPanel class.

		@param startButtonPin			The start button pin.
		@param resetButtonPin			The reset button pin.
		@param emergencyStopButtonPin	The emergency stop pin.
	*/
	ControlPanel(int startButtonPin, int resetButtonPin, int emergencyStopButtonPin);

	/**
		Deconstruct the instance of the ControlPanel class.
	*/
	~ControlPanel();
	
	/**
		Clears any text and prints 1 to 2 rows of text to the LCD.
		
		@param data1 The string of data to print on the first row of the display.
		@param data2 The string of data to print on the second row of the display. If empty, nothing is printed.
	*/
	void Print(std::string data1, std::string data2 = "");

	/**
		Indicates that the start button was pressed.
	*/
	void StartButtonPressedEvent(Machine* machine);

	/**
		Indicates that the reset button was pressed.
	*/
	void ResetButtonPressedEvent(Machine* machine);

	/**
		Indicates that the emergency stop button was pressed.
	*/
	void EmergencyStopButtonPressedEvent(Machine* machine);
	
	/**
		Gets the start button pin.
		
		@return The start button pin.
	*/
	int GetStartButtonPin();

	/**
		Gets the reset button pin.
		
		@return The reset button pin.
	*/
	int GetResetButtonPin();

	/**
		Gets the emergency stop button pin.
		
		@return The emergency stop button pin.
	*/
	int GetEmergencyStopButtonPin();
};

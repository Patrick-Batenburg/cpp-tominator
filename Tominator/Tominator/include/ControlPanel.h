#pragma once
#include "RotaryEncoder.h"
#include "EasyButton.h"
#include <LiquidCrystal_I2C.h>

class Machine;
class ControlPanel
{
private:
	EasyButton startButton;
	EasyButton resetButton;
	EasyButton emergencyStopButton;
	RotaryEncoder rotaryEncoder;
	LiquidCrystal_I2C lcd;

public:
	/**
		Initializes a new instance of the ControlPanel class.
	*/
	ControlPanel();

	/**
		Initializes a new instance of the ControlPanel class.

		@param lcd						The LCD display object.
		@param rotaryEncoder			The rotary encoder object.
		@param startButtonPin			The start button pin.
		@param resetButtonPin			The reset button pin.
		@param emergencyStopButtonPin	The emergency stop pin.
	*/
	ControlPanel(LiquidCrystal_I2C lcd, RotaryEncoder rotaryEncoder, EasyButton startButton, EasyButton resetButton, EasyButton emergencyStopButton);

	/**
		Deconstruct the instance of the ControlPanel class.
	*/
	~ControlPanel();
	
	/**
		Clears any text and prints 1 to 2 rows of text to the LCD.
		
		@param data1 The string of data to print on the first row of the display.
		@param data2 The string of data to print on the second row of the display. If empty, nothing is printed.
	*/
	void Print(String data1, String data2 = "");
	
	/**
		Gets the start button object.
		
		@return The start button object.
	*/
	EasyButton GetStartButton();

	/**
		Gets the reset button object.
		
		@return The reset button object.
	*/
	EasyButton GetResetButton();

	/**
		Gets the emergency stop button object.
		
		@return The emergency stop button object.
	*/
	EasyButton GetEmergencyStopButton();

	/**
		Gets the rotary encoder object.
		
		@return The rotary encoder object.
	*/
	RotaryEncoder GetRotaryEncoder();
};

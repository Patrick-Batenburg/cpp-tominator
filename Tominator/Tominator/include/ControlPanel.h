#pragma once
#include "RotaryEncoder.h"
#include <LiquidCrystal_I2C.h>

class Machine;
class ControlPanel
{
private:
	int startButtonPin;
	int resetButtonPin;
	int emergencyStopButtonPin;
	RotaryEncoder rotaryEncoder;
	LiquidCrystal_I2C lcd;

public:
	/**
		Initializes a new instance of the ControlPanel class.
	*/
	ControlPanel();

	/**
		Initializes a new instance of the ControlPanel class.
	*/
	ControlPanel(LiquidCrystal_I2C lcd);


	/**
		Initializes a new instance of the ControlPanel class.

		@param lcd						The LCD display object.
		@param rotaryEncoder			The rotary encoder object.
		@param startButtonPin			The start button pin.
		@param resetButtonPin			The reset button pin.
		@param emergencyStopButtonPin	The emergency stop pin.
	*/
	ControlPanel(LiquidCrystal_I2C lcd, RotaryEncoder rotaryEncoder, int startButtonPin, int resetButtonPin, int emergencyStopButtonPin);

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
		Turns a LED on. Has options for blinking and how often it should blink.

		@param ledPin				The pin of the LED.		
		@param blinking				Determines whenever or not the LED should blink. Default value = true.		
		@param delayInMilliseconds	The delay in milliseconds that is needed for blinking. Default value = 1000.
	*/
	void TurnOnLED(int ledPin, bool blinking = true, int delayInMilliseconds = 1000);

	/**
		Turns a LED off.

		@param ledPin				The pin of the LED.
	*/	
	void TurnOffLED(int ledPin);
	
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

	/**
		Gets the rotary encoder object.
		
		@return The rotary encoder object.
	*/
	RotaryEncoder GetRotaryEncoder();
};

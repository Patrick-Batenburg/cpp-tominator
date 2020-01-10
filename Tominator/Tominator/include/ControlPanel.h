#pragma once
#include "RotaryEncoder.h"
#include <EasyButton.h>
#include <LiquidCrystal_I2C.h>
#include <jled.h>
#include <pins_arduino.h>

class Machine;
class ControlPanel
{
private:
	JLed startLed = JLed(LED_BUILTIN);
	JLed resetLed = JLed(LED_BUILTIN);
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

		@param lcd					The LCD display object.
		@param rotaryEncoder		The rotary encoder object.
		@param startButton			The start button.
		@param resetButton			The reset button.
		@param emergencyStopButton	The emergency stop.
		@param startLed				The built-in LED in the start button.
		@param resetLed				The built-in LED in the reset button.
	*/
	ControlPanel(LiquidCrystal_I2C lcd, RotaryEncoder rotaryEncoder, EasyButton startButton, EasyButton resetButton, EasyButton emergencyStopButton, JLed startLed, JLed resetLed);

	/**
		Deconstruct the instance of the ControlPanel class.
	*/
	~ControlPanel();

	/**
		Clears any text and prints 1 to 2 rows of text to the LCD.
		
		@param data1 The string of data to print on the first row of the display. If empty, nothing is printed.
		@param data2 The string of data to print on the second row of the display. If empty, nothing is printed.
	*/
	void Print(String data1, String data2 = "");

	/**
		Clears any text present on the LCD.
	*/
	void Clear();

	/**
		Read the status of the buttons. Use in the loop() method to continuously read the status.
	*/
	void ReadButtons();

	/**
		Updates the status of the LEDs. Use in the loop() method to continuously update the status.
	*/
	void UpdateLeds();

	/**
		Configures the built-in LED in the the start button to be turned on.
	*/
	void ConfigureStartLedOn();

	/**
		Configures the built-in LED in the the start button to be turned off.
	*/
	void ConfigureStartLedOff();

	/**
		Configures the built-in LED in the the reset button to be turned on.
	*/
	void ConfigureResetLedOn();

	/**
		Configures the built-in LED in the the reset button to be turned off.
	*/
	void ConfigureResetLedOff();

	/**
		Configures the built-in LED in the the start button to blink slowly.
	*/
	void ConfigureBootUpLed();

	/**
		Configures the built-in LED in the the reset button to blink slowly.
	*/
	void ConfigureStandbyLed();

	/**
		Configures the built-in LED in the the start button to blink every 1 second.
	*/
	void ConfigureInitializeLed();

	/**
		Configures the built-in LED in the the start button to blink quickly.
	*/
	void ConfigureRunningLed();

	/**
		Configures the built-in LED in the the reset button to blink very quickly.
	*/
	void ConfigureEmergencyLed();

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

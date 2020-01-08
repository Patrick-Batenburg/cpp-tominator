#include "Machine.h"
#include "EmergencyState.h"
#include <ArduinoSTL.h>
#include <EasyButton.h>
#include <jled.h>
#include <MemoryFree.h>

Machine machine;
EasyButton startButton = EasyButton(PIN_START_BUTTON);
EasyButton resetButton = EasyButton(PIN_RESET_BUTTON);
EasyButton emergencyButton = EasyButton(PIN_EMERGENCY_STOP_BUTTON);

JLed LED1Off = JLed(P1_LED_STATE).Off();
JLed LED2Off = JLed(P2_LED_STANDBY_EMERGENCY).Off();
JLed bootUpStateLED = JLed(P1_LED_STATE);
JLed standbyStateLED = JLed(P2_LED_STANDBY_EMERGENCY);
JLed initializeStateLED = JLed(P1_LED_STATE);
JLed runningStateLED = JLed(P1_LED_STATE);
JLed emergencyStateLED = JLed(P2_LED_STANDBY_EMERGENCY);

inline const String ToString(WaterBalloonType value)
{
	switch (value)
	{
		case WaterBalloonType::Empty:
		return "Empty";
		case WaterBalloonType::Small:
		return "Small";
		case WaterBalloonType::Medium:
		return "Medium";
		case WaterBalloonType::Large:
		return "Large";
		case WaterBalloonType::Unkown:
		return "Unkown";
		default:
		return "No value";
	}
}

void DefaultModeTest()
{
	String row = "Row 1: ";
	
	Serial.println("State Test:");

	Serial.print("Current state: " + machine.GetState()->ToString());
	Serial.println();
	Serial.println();
	
	machine.ResetButtonPressed();
	Serial.print("Current state: " + machine.GetState()->ToString());
	Serial.println();
	Serial.println();
	
	machine.StartButtonPressed();
	Serial.print("Current state: " + machine.GetState()->ToString());
	Serial.println();
	Serial.println();
	
	//machine.EmergencyStopButtonPressed();
	//Serial.print("Current state: " + machine.GetState()->ToString());
	//Serial.println();
	//Serial.println();
	
	machine.StartButtonPressed();
	Serial.print("Current state: " + machine.GetState()->ToString());
	Serial.println();
	Serial.println();
	
	//machine.EmergencyStopButtonPressed();
	//Serial.print("Current state: " + machine.GetState()->ToString());
	//Serial.println();
	//Serial.println();

	
	Serial.println("Grid Before");
	
	for (int i = 0; i < machine.GetGrid().GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetGrid().GetWaterBalloonPositions()[i].size(); j++)
		{
			WaterBalloon waterBalloon = WaterBalloon(machine.GetGrid().GetWaterBalloonPositions()[i][j].GetWeight());
			Serial.print(waterBalloon.GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println("Conveyor Belt:");
	
	for (int i = 0; i < machine.GetConveyorBelt().GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetConveyorBelt().GetWaterBalloonPositions()[i].size(); j++)
		{
			Serial.print(machine.GetConveyorBelt().GetWaterBalloonPositions()[i][j].GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println("Grid After:");
	
	for (int i = 0; i < machine.GetGrid().GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetGrid().GetWaterBalloonPositions()[i].size(); j++)
		{
			Serial.print(machine.GetGrid().GetWaterBalloonPositions()[i][j].GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println(row + ToString(machine.GetConveyorBelt().GetFirstRowType()));
	
	row = "Row 2: ";
	Serial.println(row + ToString(machine.GetConveyorBelt().GetSecondRowType()));
	
	
	row = "Row 3: ";
	Serial.println(row + ToString(machine.GetConveyorBelt().GetThirdRowType()));
	Serial.println();
	Serial.print("transported water balloons: ");
	Serial.println(machine.GetConveyorBelt().GetTransportedWaterBalloons());
	Serial.println();

	machine.EmergencyStopButtonPressed();
	Serial.print("Current state: " + machine.GetState()->ToString());
	Serial.println();
	Serial.println();
	machine.ResetButtonPressed();

}


void OnStartButtonPressed()
{
	machine.StartButtonPressed();
	Serial.println("OnStartButtonPressed()");
}

void OnResetButtonPressed()
{
	machine.ResetButtonPressed();
	Serial.println("OnResetButtonPressed()");
	
	//switch (machine.GetState()->GetStateTypes()[machine.GetState()->ToString()])
	//{
		//case BaseMachineStateType::RunningStateType:
		//machine.SetState(new EmergencyState());
		//break;
	//}
}

void OnEmergencyButtonPressed()
{
	machine.EmergencyStopButtonPressed();
	Serial.println("OnEmergencyButtonPressed()");
}

void ConfigureLEDs()
{
	bootUpStateLED.Blink(2000, 1000);
	bootUpStateLED.Forever();
	standbyStateLED.Blink(2000, 1000);
	standbyStateLED.Forever();
	initializeStateLED.Blink(1000, 500);
	initializeStateLED.Forever();
	runningStateLED.On();
	emergencyStateLED.Blink(300, 150);
	emergencyStateLED.Forever();
}

void HandleLEDs()
{
	switch (machine.GetState()->GetStateTypes()[machine.GetState()->ToString()])
    {
		case BaseMachineStateType::BootUpStateType:
			bootUpStateLED.Update();
			break;
		case BaseMachineStateType::StandbyStateType:
			standbyStateLED.Update();
			break;
		case BaseMachineStateType::InitializeStateType:
			initializeStateLED.Update();
			break;
		case BaseMachineStateType::RunningStateType:
			runningStateLED.Update();
			machine.SetState(new EmergencyState());
			break;
		case BaseMachineStateType::BaseMachineType:
		default:
			emergencyStateLED.Update();
			break;
    }
}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);		
	LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
	lcd.init();
	lcd.backlight();
	
	startButton.begin();
	resetButton.begin();
	emergencyButton.begin();
	startButton.onPressed(OnStartButtonPressed);
	resetButton.onPressed(OnResetButtonPressed);
	emergencyButton.onPressed(OnEmergencyButtonPressed);

	//ConfigureLEDs();
	
	ControlPanel controlPanel = ControlPanel(lcd, RotaryEncoder(S4_ROTARY_ENCODER_CLK, S4_ROTARY_ENCODER_DT), startButton, resetButton, emergencyButton);
	machine = Machine(controlPanel);
	Serial.begin(9600);
}

void loop()
{
	startButton.read();
	resetButton.read();
	emergencyButton.read();
    //HandleLEDs();
	DefaultModeTest();

	Serial.print("Memory: ");
	Serial.println(freeMemory(), DEC); 
	delay(1000);
}

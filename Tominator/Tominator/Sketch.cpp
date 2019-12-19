#include "Machine.h"
#include <ArduinoSTL.h>
#include <Arduino_FreeRTOS.h>
#include <croutine.h>
#include <event_groups.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOSVariant.h>
#include <list.h>
#include <mpu_wrappers.h>
#include <portable.h>
#include <portmacro.h>
#include <projdefs.h>
#include <queue.h>
#include <semphr.h>
#include <stack_macros.h>
#include <task.h>
#include <timers.h>
#include "Mode8_SwitchingModes.h"
#include "RunningState.h"
#include "StandbyState.h"
#include "stdlib.h"

using namespace std;

Machine machine;
SemaphoreHandle_t semaphore;

void TaskMain(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

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
	
	cout << "State Test:" << endl;
	cout << "Current state: " << machine.GetState()->ToString() << endl << endl;
	
	machine.ResetButtonPressed();
	cout << "ResetButtonPressed: " << endl;
	cout << "Current state: " << machine.GetState()->ToString() << endl << endl;
	
	machine.StartButtonPressed();
	cout << "StartButtonPressed: " << endl;
	cout << "Current state: " << machine.GetState()->ToString() << endl << endl;
	
	//machine.EmergencyStopButtonPressed();
	//cout << "EmergencyStopButtonPressed: " << endl;
	//cout << "Current state: " << machine.GetState()->ToString() << endl << endl;
	
	machine.StartButtonPressed();
	cout << "StartButtonPressed: " << endl;
	cout << "Current state: " << machine.GetState()->ToString() << endl << endl;
	

	machine.EmergencyStopButtonPressed();
	cout << "EmergencyStopButtonPressed: " << endl;
	cout << "Current state: " << machine.GetState()->ToString() << endl << endl;

	
	cout << "Grid Before:" << endl;
	
	for (int i = 0; i < machine.GetGrid().GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetGrid().GetWaterBalloonPositions()[i].size(); j++)
		{
			WaterBalloon waterBalloon = WaterBalloon(machine.GetGrid().GetWaterBalloonPositions()[i][j].GetWeight());
			cout << waterBalloon.GetType() << " ";
		}
		
		cout << endl;
	}
	
	cout << endl;
	cout << "Conveyor Belt:" << endl;
	
	for (int i = 0; i < machine.GetConveyorBelt().GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetConveyorBelt().GetWaterBalloonPositions()[i].size(); j++)
		{
			cout << machine.GetConveyorBelt().GetWaterBalloonPositions()[i][j].GetType() << " ";
		}
		
		cout << endl;
	}
	
	cout << endl;
	cout << "Grid After:" << endl;
	
	for (int i = 0; i < machine.GetGrid().GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetGrid().GetWaterBalloonPositions()[i].size(); j++)
		{
			cout << machine.GetGrid().GetWaterBalloonPositions()[i][j].GetType() << " ";
		}
		
		cout << endl;
	}
	
	cout << endl;
	cout << row + ToString(machine.GetConveyorBelt().GetFirstRowType()) << endl;
	
	row = "Row 2: ";
	cout << row + ToString(machine.GetConveyorBelt().GetSecondRowType()) << endl;
	
	
	row = "Row 3: ";
	cout << row + ToString(machine.GetConveyorBelt().GetThirdRowType()) << endl;
	cout << endl;
	cout << "transported water balloons: " << machine.GetConveyorBelt().GetTransportedWaterBalloons() << endl << endl;
}

void InterruptHandler()
{
	xSemaphoreGiveFromISR(semaphore, NULL);
}

void setup()
{
	// Semaphores are useful to stop a Task proceeding, where it should be paused to wait, because it is sharing a resource
	// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	if (semaphore == NULL)  // Check to confirm that the Semaphore has not already been created.
	{
		semaphore = xSemaphoreCreateBinary();
		
		if (semaphore != NULL)
		{
			xSemaphoreGive(semaphore);
		}
	}
	
	// Use falling edge interrupt for resuming tasks. DIGITAL PINS USABLE FOR INTERRUPTS: 2, 3, 18, 19, 20, 21
	attachInterrupt(digitalPinToInterrupt(18), InterruptHandler, RISING);
	
	//			Function		Name								Stack size		Priority
	xTaskCreate(TaskMain,		(const portCHAR *) "Blink",			128,	NULL,	1,  NULL);
	xTaskCreate(TaskAnalogRead, (const portCHAR *) "AnalogRead",	128,	NULL,	2,  NULL);
	
	pinMode(LED_BUILTIN, OUTPUT);
		
	pinMode(P1_LED_STATE, OUTPUT);
	pinMode(P2_LED_STANDBY_EMERGENCY, OUTPUT);
	Serial.begin(9600);
	LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
	machine = Machine(lcd);	
	
	//DefaultModeTest();
	
	//machine.SetState(new StandbyState());
	//machine.SetMode(new SwitchingModesMode());
	//machine.SetState(new RunningState());
	//
	//machine.StartMode();
	Machine* machinePtr = &machine;
	
	vTaskStartScheduler();
}

int buttonState;
int i = 0;
String converted;

void loop()
{	
	//DefaultModeTest();

	i++;
	converted = String(i);
	
	buttonState = digitalRead(PIN_START_BUTTON);

	// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
	if (buttonState == HIGH)
	{
		machine.StartButtonPressed();
	}
	
	buttonState = digitalRead(PIN_RESET_BUTTON);

	// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
	if (buttonState == HIGH)
	{
		machine.ResetButtonPressed();
	}
	

	switch (machine.GetState()->GetStateTypes()[machine.GetState()->ToString()])
	{
		case BaseMachineStateType::BootUpStateType:
			machine.GetControlPanel().TurnOnLED(P1_LED_STATE, false);
			break;
		case BaseMachineStateType::StandbyStateType:
			machine.GetControlPanel().TurnOnLED(P2_LED_STANDBY_EMERGENCY);
			//machine.GetControlPanel().TurnOffLED(P1_LED_STATE);
			//delay(1000);
			break;
		case BaseMachineStateType::InitializeStateType:
			machine.GetControlPanel().TurnOnLED(P1_LED_STATE);
			break;
		case BaseMachineStateType::RunningStateType:
			machine.GetControlPanel().TurnOnLED(P1_LED_STATE, true, 500);
			break;
		case BaseMachineStateType::BaseMachineType:
		default:
			machine.GetControlPanel().TurnOnLED(P1_LED_STATE, true, 250);
			machine.GetControlPanel().TurnOnLED(P2_LED_STANDBY_EMERGENCY, true, 250);
			break;
	}
	
	buttonState = digitalRead(PIN_EMERGENCY_STOP_BUTTON);

	// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
	if (buttonState == LOW) 
	{
		machine.GetControlPanel().TurnOnLED(P1_LED_STATE, true, 250);
		machine.GetControlPanel().TurnOnLED(P2_LED_STANDBY_EMERGENCY, true, 250);
	}
	
	//if (machine.GetState()->ToString() == BOOT_UP_STATE)
	//{
		//machine.GetControlPanel().TurnOnLED(P1_LED_STATE, false);
	//}
	//else if (machine.GetState()->ToString() == INITIALIZE_STATE)
	//{
		//machine.GetControlPanel().TurnOnLED(P1_LED_STATE);
	//}
	//else if (machine.GetState()->ToString() == RUNNING_STATE)
	//{
		//machine.GetControlPanel().TurnOnLED(P1_LED_STATE, true, 500);
	//}
	//else if (machine.GetState()->ToString() == STANDBY_STATE)
	//{
		//machine.GetControlPanel().TurnOffLED(P1_LED_STATE);
		//machine.GetControlPanel().TurnOnLED(P2_LED_STANDBY_EMERGENCY);
	//}	
	//else
	//{		
		//machine.GetControlPanel().TurnOnLED(P1_LED_STATE, true, 250);
		//machine.GetControlPanel().TurnOnLED(P2_LED_STANDBY_EMERGENCY, true, 250);
	//}
}


/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskMain(void *pvParameters)  // This is a task.
{
	(void) pvParameters;

	for (;;) // A Task shall never return or exit.
	{
		// See if we can obtain or "Take" the Serial Semaphore.
		// If the semaphore is not available, wait a indefinitely amount of ticks of the Scheduler to see if it becomes free.
		if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdPASS)
		{
			// We were able to obtain or "Take" the semaphore and can now access the shared resource.
			
			digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
			vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
			digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
			vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second

			xSemaphoreGive(semaphore); // Now free or "Give" the Serial Port for others.
		}

		vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
	}	
}

void TaskAnalogRead(void *pvParameters __attribute__((unused)))
{
	for (;;)
	{
		// read the input on analog pin 0:
		int sensorValue = analogRead(A0);

		// See if we can obtain or "Take" the Serial Semaphore.
		// If the semaphore is not available, wait a indefinitely amount of ticks of the Scheduler to see if it becomes free.
		if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdPASS)
		{
			// We were able to obtain or "Take" the semaphore and can now access the shared resource.
			// We want to have the Serial Port for us alone, as it takes some time to print,
			// so we don't want it getting stolen during the middle of a conversion.
			// print out the value you read:
			Serial.println(sensorValue);

			xSemaphoreGive(semaphore); // Now free or "Give" the Serial Port for others.
		}

		vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
	}
}
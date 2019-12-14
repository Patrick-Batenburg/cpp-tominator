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

using namespace std;

Machine machine;
SemaphoreHandle_t semaphore;

void TaskMain(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

inline const string ToString(WaterBalloonType value)
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
	string row = "Row 1: ";
	
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
	
	// Use INT0(pin2) falling edge interrupt for resuming tasks
	attachInterrupt(digitalPinToInterrupt(2), InterruptHandler, RISING);
	
	//			Function		Name								Stack size		Priority
	xTaskCreate(TaskMain,		(const portCHAR *) "Blink",			128,	NULL,	1,  NULL);
	xTaskCreate(TaskAnalogRead, (const portCHAR *) "AnalogRead",	128,	NULL,	2,  NULL);
	
	pinMode(LED_BUILTIN, OUTPUT);
		
	pinMode(PIN_START, INPUT);
	pinMode(PIN_RESET, INPUT);
	pinMode(PIN_EMERGENCY_STOP, INPUT);
	
	pinMode(PIN_ENABLE_STEPPER_MOTOR, OUTPUT);
	
	pinMode(REED1_GRID, INPUT);
	pinMode(REED2_SORTING_SIDE, INPUT);
	pinMode(REED3_CONVEYOR_BELT, INPUT);
	pinMode(REED6_HOMING_Y, INPUT);
	pinMode(REED7_HOMING_X, INPUT);
	pinMode(REED8_HOMING_Z, INPUT);
	pinMode(REED9_HOMING_CLAW, INPUT);
	
	pinMode(P1_LED_STATE, OUTPUT);
	pinMode(P2_LED_STANDBY_EMERGENCY, OUTPUT);

	pinMode(PIN_A0, OUTPUT);
	pinMode(PIN_A1, OUTPUT);
	
	Serial.begin(9600);
	machine = Machine();	
	DefaultModeTest();
	vTaskStartScheduler();
}

void loop()
{	
	//digitalWrite(LED_BUILTIN, HIGH);
	//delay(1000);
	//digitalWrite(LED_BUILTIN, LOW);
	//delay(1000);
	
	DefaultModeTest();
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
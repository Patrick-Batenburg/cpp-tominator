﻿#include "Machine.h"
#include "EmergencyState.h"
#include <ArduinoSTL.h>
#include <EasyButton.h>
#include <jled.h>
#include <MemoryFree.h>
//#include <Arduino_FreeRTOS.h>
//#include <croutine.h>
//#include <event_groups.h>
//#include <FreeRTOSConfig.h>
//#include <FreeRTOSVariant.h>
//#include <list.h>
//#include <mpu_wrappers.h>
//#include <portable.h>
//#include <portmacro.h>
//#include <projdefs.h>
//#include <queue.h>
//#include <semphr.h>
//#include <stack_macros.h>
//#include <task.h>
//#include <timers.h>

static long const loadCellOffset = 50682624;
static long const loadCellDivider = 5895655;

Machine machine;
EasyButton startButton = EasyButton(PIN_START_BUTTON);
EasyButton resetButton = EasyButton(PIN_RESET_BUTTON);
EasyButton emergencyButton = EasyButton(PIN_EMERGENCY_STOP_BUTTON);

//SemaphoreHandle_t semaphore;
//void TaskMain(void* pvParameters);
//void TaskAnalogRead(void* pvParameters);

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
	
	for (int i = 0; i < machine.GetGrid()->GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetGrid()->GetWaterBalloonPositions()[i].size(); j++)
		{
			WaterBalloon waterBalloon = WaterBalloon(machine.GetGrid()->GetWaterBalloonPositions()[i][j].GetWeight());
			Serial.print(waterBalloon.GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println("Conveyor Belt:");
	
	for (int i = 0; i < machine.GetConveyorBelt()->GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetConveyorBelt()->GetWaterBalloonPositions()[i].size(); j++)
		{
			Serial.print(machine.GetConveyorBelt()->GetWaterBalloonPositions()[i][j].GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println("Grid After:");
	
	for (int i = 0; i < machine.GetGrid()->GetWaterBalloonPositions().size(); i++)
	{
		for (int j = 0; j < machine.GetGrid()->GetWaterBalloonPositions()[i].size(); j++)
		{
			Serial.print(machine.GetGrid()->GetWaterBalloonPositions()[i][j].GetType());
			Serial.print(" ");
		}
		
		Serial.println();
	}
	
	Serial.println();
	Serial.println(row + ToString(machine.GetConveyorBelt()->GetFirstRowType()));
	
	row = "Row 2: ";
	Serial.println(row + ToString(machine.GetConveyorBelt()->GetSecondRowType()));
	
	row = "Row 3: ";
	Serial.println(row + ToString(machine.GetConveyorBelt()->GetThirdRowType()));
	Serial.println();
	Serial.print("transported water balloons: ");
	Serial.println(machine.GetConveyorBelt()->GetTransportedWaterBalloons());
	Serial.println();

	machine.EmergencyStopButtonPressed();
	Serial.print("Current state: " + machine.GetState()->ToString());
	Serial.println();
	Serial.println();
	machine.ResetButtonPressed();
}

void OnStartButtonPressed()
{
	delay(500);
	machine.StartButtonPressed();
	Serial.println("OnStartButtonPressed()");	
}

void OnResetButtonPressed()
{
	delay(500);
	machine.ResetButtonPressed();
	Serial.println("OnResetButtonPressed()");
}

void OnEmergencyButtonPressed()
{
	delay(500);
	machine.EmergencyStopButtonPressed();
	Serial.println("OnEmergencyButtonPressed()");
}

//void InterruptHandler()
//{
	//xSemaphoreGiveFromISR(semaphore, NULL);
//}

void setup()
{	
	//// Semaphores are useful to stop a Task proceeding, where it should be paused to wait, because it is sharing a resource
	//// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	//if (semaphore == NULL)  // Check to confirm that the Semaphore has not already been created.
	//{
		//semaphore = xSemaphoreCreateBinary();
		//
		//if (semaphore != NULL)
		//{
			//xSemaphoreGive(semaphore);
		//}
	//}
	//// Use falling edge interrupt for resuming tasks. DIGITAL PINS USABLE FOR INTERRUPTS: 2, 3, 18, 19, 20, 21
	//attachInterrupt(digitalPinToInterrupt(18), InterruptHandler, RISING);
	//
	////			Function		Name								Stack size		Priority
	//xTaskCreate(TaskMain,		(const portCHAR *) "Blink",			128,	NULL,	1,  NULL);
	//xTaskCreate(TaskAnalogRead, (const portCHAR *) "AnalogRead",	128,	NULL,	2,  NULL);
		
	pinMode(LED_BUILTIN, OUTPUT);
	
	DCMotor conveyorBeltDCMotor = DCMotor(PIN_CONVEYOR_BELT_IN1_DIRECTION, PIN_CONVEYOR_BELT_IN2_DIRECTION, PIN_CONVEYOR_BELT_PWM);
	DCMotor carriageDCMotor = DCMotor(PIN_CARRIAGE_IN1_DIRECTION, PIN_CARRIAGE_IN2_DIRECTION, PIN_CARRIAGE_PWM);
	DCMotor frameDCMotor = DCMotor(PIN_FRAME_IN1_DIRECTION, PIN_FRAME_IN2_DIRECTION, PIN_FRAME_PWM);
	UltrasonicSensor gridSideSensor = UltrasonicSensor(B1_ULTRASONIC_TRIGGER, B1_ULTRASONIC_ECHO);
	UltrasonicSensor sortingSideSensor = UltrasonicSensor(B2_ULTRASONIC_TRIGGER, B2_ULTRASONIC_ECHO);
	Claw claw = Claw(STP_CLAW_PULSE, STP_CLAW_DIRECTION, REED9_HOMING_CLAW);
	Grid* grid = new Grid();

	ConveyorBelt* conveyorBelt = new ConveyorBelt(conveyorBeltDCMotor, REED3_CONVEYOR_BELT);
	Frame frame = Frame(frameDCMotor, gridSideSensor, sortingSideSensor, REED1_GRID_SIDE, REED2_SORTING_SIDE, grid, conveyorBelt);
	Carriage carriage = Carriage(carriageDCMotor, HALL_CARRIAGE_BOTTOM, HALL_CARRIAGE_MIDDLE, HALL_CARRIAGE_TOP);
	RobotArm robotArm = RobotArm(STP_X_PULSE, STP_X_DIRECTION, REED7_HOMING_X, STP_Y_PULSE, STP_Y_DIRECTION, REED6_HOMING_Y, STP_Z_PULSE, STP_Z_DIRECTION, REED8_HOMING_Z, claw);
	RotaryEncoder rotaryEncoder = RotaryEncoder(S4_ROTARY_ENCODER_CLK, S4_ROTARY_ENCODER_DT);
	JLed* startLed = new JLed(START_LED_STATE);
	JLed* resetLed = new JLed(RESET_LED_STATE);
	HX711 loadCell;
	loadCell.begin(HX1_LOAD_CELL_DT, HX1_LOAD_CELL_SCK);	
	
	startButton.begin();
	startButton.onPressed(OnStartButtonPressed);
	resetButton.begin();
	resetButton.onPressed(OnResetButtonPressed);
	emergencyButton.begin();
	emergencyButton.onPressed(OnEmergencyButtonPressed);
	
	LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
	lcd.init();
	lcd.backlight();

	ControlPanel controlPanel = ControlPanel(lcd, rotaryEncoder, startButton, resetButton, emergencyButton, startLed, resetLed);

	machine = Machine(grid, conveyorBelt, frame, carriage, robotArm, loadCell, controlPanel);
	Serial.begin(9600);
	//vTaskStartScheduler();
}

void loop()
{
	machine.GetControlPanel().UpdateLeds();
	machine.GetControlPanel().ReadButtons();
	//DefaultModeTest();

	Serial.print("Memory: ");
	Serial.println(freeMemory(), DEC); 
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

//void TaskMain(void* pvParameters)  // This is a task.
//{
	//(void) pvParameters;
//
	//for (;;) // A Task shall never return or exit.
	//{
		//// See if we can obtain or "Take" the Serial Semaphore.
		//// If the semaphore is not available, wait a indefinitely amount of ticks of the Scheduler to see if it becomes free.
		//if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdPASS)
		//{
			//// We were able to obtain or "Take" the semaphore and can now access the shared resource.
			//
			//digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
			//vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
			//digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
			//vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
//
			//xSemaphoreGive(semaphore); // Now free or "Give" the Serial Port for others.
		//}
//
		//vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
	//}
//}
//
//void TaskAnalogRead(void* pvParameters __attribute__((unused)))
//{
	//for (;;)
	//{
		//// read the input on analog pin 0:
		//int sensorValue = analogRead(A0);
//
		//// See if we can obtain or "Take" the Serial Semaphore.
		//// If the semaphore is not available, wait a indefinitely amount of ticks of the Scheduler to see if it becomes free.
		//if (xSemaphoreTake(semaphore, portMAX_DELAY) == pdPASS)
		//{
			//// We were able to obtain or "Take" the semaphore and can now access the shared resource.
			//// We want to have the Serial Port for us alone, as it takes some time to print,
			//// so we don't want it getting stolen during the middle of a conversion.
			//// print out the value you read:
			//Serial.println(sensorValue);
//
			//xSemaphoreGive(semaphore); // Now free or "Give" the Serial Port for others.
		//}
//
		//vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
	//}
//}
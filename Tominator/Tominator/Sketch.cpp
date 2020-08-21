#include "Machine.h"
#include "EmergencyState.h"
#include <ArduinoSTL.h>
#include <EasyButton.h>
#include <jled.h>
#include <MemoryFree.h>

static float const loadCellCalibrationFactor = 232;
EasyButton startButton = EasyButton(PIN_START_BUTTON);
EasyButton resetButton = EasyButton(PIN_RESET_BUTTON);
EasyButton emergencyButton = EasyButton(PIN_EMERGENCY_STOP_BUTTON);
HX711 loadCell;
Machine machine;

void OnStartButtonPressed()
{
	delay(500);
	machine.StartButtonPressed();
}

void OnResetButtonPressed()
{
	delay(500);
	machine.ResetButtonPressed();
}

void OnEmergencyButtonPressed()
{
	delay(500);
	machine.EmergencyStopButtonPressed();
	Serial.println("OnEmergencyButtonPressed()");
}

void setup()
{			
	pinMode(LED_BUILTIN, OUTPUT);
	loadCell.begin(HX1_LOAD_CELL_DT, HX1_LOAD_CELL_SCK);
	loadCell.set_scale(232950);
	loadCell.tare();
	
	startButton.begin();
	resetButton.begin();
	emergencyButton.begin();
	startButton.onPressed(OnStartButtonPressed);
	resetButton.onPressed(OnResetButtonPressed);
	emergencyButton.onPressed(OnEmergencyButtonPressed);
	
	LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
	lcd.init();
	lcd.backlight();
	
	JLed* startLed = new JLed(START_LED_STATE);
	JLed* resetLed = new JLed(RESET_LED_STATE);
	DCMotor* conveyorBeltDCMotor = new DCMotor(PIN_CONVEYOR_BELT_IN1_DIRECTION, PIN_CONVEYOR_BELT_IN2_DIRECTION, PIN_CONVEYOR_BELT_PWM);
	DCMotor* carriageDCMotor = new DCMotor(PIN_CARRIAGE_IN1_DIRECTION, PIN_CARRIAGE_IN2_DIRECTION, PIN_CARRIAGE_PWM);
	DCMotor* frameDCMotor = new DCMotor(PIN_FRAME_IN1_DIRECTION, PIN_FRAME_IN2_DIRECTION, PIN_FRAME_PWM);
	UltrasonicSensor gridSideSensor = UltrasonicSensor(B1_ULTRASONIC_TRIGGER, B1_ULTRASONIC_ECHO);
	UltrasonicSensor sortingSideSensor = UltrasonicSensor(B2_ULTRASONIC_TRIGGER, B2_ULTRASONIC_ECHO);
	Claw claw = Claw(STP_CLAW_PULSE, STP_CLAW_DIRECTION, REED9_HOMING_CLAW);
	Grid* grid = new Grid();

	ConveyorBelt* conveyorBelt = new ConveyorBelt(conveyorBeltDCMotor, REED3_CONVEYOR_BELT);
	Frame frame = Frame(frameDCMotor, gridSideSensor, sortingSideSensor, REED1_GRID_SIDE, REED2_SORTING_SIDE, grid, conveyorBelt);
	Carriage carriage = Carriage(carriageDCMotor, HALL_CARRIAGE_BOTTOM, HALL_CARRIAGE_MIDDLE, HALL_CARRIAGE_TOP);
	RobotArm robotArm = RobotArm(STP_X_PULSE, STP_X_DIRECTION, REED7_HOMING_X, STP_Y_PULSE, STP_Y_DIRECTION, REED6_HOMING_Y, STP_Z_PULSE, STP_Z_DIRECTION, REED8_HOMING_Z, claw);
	RotaryEncoder* rotaryEncoder = new RotaryEncoder(S4_ROTARY_ENCODER_CLK, S4_ROTARY_ENCODER_DT);
	ControlPanel controlPanel = ControlPanel(lcd, rotaryEncoder, startButton, resetButton, emergencyButton, startLed, resetLed);

	machine = Machine(grid, conveyorBelt, frame, carriage, robotArm, loadCell, controlPanel);
	Serial.begin(9600);
}

void loop()
{
	machine.GetControlPanel().Update();
	machine.SelectMode(machine.GetControlPanel().GetRotaryEncoder()->GetCounter());
	
	//Serial.print("Memory: ");
	//Serial.println(freeMemory(), DEC);
	//delay(500);
}
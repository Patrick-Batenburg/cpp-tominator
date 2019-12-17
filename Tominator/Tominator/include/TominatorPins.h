#pragma once
#include <pins_arduino.h>

#define PIN_FRAME_IN1_DIRECTION 2			// frame aandrijving IN1 richting
#define PIN_FRAME_IN2_DIRECTION 3			// frame aandrijving IN2 richting
#define PIN_FRAME_PWM 4						// frame aandrijving PWM

#define PIN_CARRIAGE_IN1_DIRECTION 5		// carriage aandrijving IN1 richting
#define PIN_CARRIAGE_IN2_DIRECTION 6		// carriage aandrijving IN2 richting
#define PIN_CARRIAGE_PWM 7					// carriage aandrijving PWM

#define PIN_CONVEYOR_BELT_IN1_DIRECTION 8	// Transportband IN1 richting
#define PIN_CONVEYOR_BELT_IN2_DIRECTION 9	// Transportband IN2 richting
#define PIN_CONVEYOR_BELT_PWM 10			// Transportband PWM

#define PIN_START_BUTTON 15					// Startknop N/O
#define PIN_RESET_BUTTON 17					// Resetknop N/C
#define PIN_EMERGENCY_STOP_BUTTON 19		// Noodstop N/O

#define PIN_ENABLE_STEPPER_MOTOR 30			// Stappenmotoren enable
#define STP_X_PULSE 24						// STP1 X-as Pulse
#define STP_X_DIRECTION 25					// STP1 X-as Direction
#define STP_Y_PULSE 22						// STP2 Y-as Pulse
#define STP_Y_DIRECTION 23					// STP2 Y-as Direction
#define STP_Z_PULSE 26						// STP3 Z-as Pulse
#define STP_Z_DIRECTION 27					// STP3 Z-as Direction
#define STP_CLAW_PULSE 28					// STP4 grijper Pulse
#define STP_CLAW_DIRECTION 29				// STP4 grijper Direction

#define REED1_GRID_SIDE 31					// Reed1 - Einde bovenloop as pallet
#define REED2_SORTING_SIDE 32				// Reed2 - Einde bovenloop as uitsorteerkant
#define HALL_CARRIAGE_TOP 33				// Hall1 - Hoogte carriage positie boven
#define HALL_CARRIAGE_MIDDLE 34				// Hall2 - Hoogte carriage positie midden
#define HALL_CARRIAGE_BOTTOM 35				// Hall3 - Hoogte carriage positie beneden
#define REED3_CONVEYOR_BELT 36				// Reed3 - Transportband
#define REED6_HOMING_Y 37					// Reed6 - Homing Y-as
#define REED7_HOMING_X 38					// Reed7 - Homing X-as
#define REED8_HOMING_Z 39					// Reed8 - Homing Z-as
#define REED9_HOMING_CLAW 40				// Reed9 - Homing grijper
#define HX1_LOAD_CELL_SCK 41				// HX1 - SCK load cell
#define HX1_LOAD_CELL_DT 42					// HX1 - DT load cell

#define P1_LED_STATE 43						// P1 - led In bedrijf
#define P2_LED_STANDBY_EMERGENCY 44			// P2 - Led Standby/Noodstop

#define S4_ROTARY_ENCODER_DT 45				// S4 - Mode selectie, Rotary Encoder DT
#define S4_ROTARY_ENCODER_CLK 46			// S4 - Mode selectie, Rotary Encoder CLK

#define B1_ULTRASONIC_TRIGGER 47			// B1 Ultrasoon Trig
#define B1_ULTRASONIC_ECHO 48				// B1 Ultrasoon Echo
#define B2_ULTRASONIC_TRIGGER 49			// B2 Ultrasoon Trig
#define B2_ULTRASONIC_ECHO 50				// B2 Ultrasoon Echo

// Display SDA, defined in pins_arduino.h as SDA
// Display SCL, defined in pins_arduino.h as SCL

#include "Carriage.h"
#include "TominatorPins.h"

Carriage::Carriage()
{
}

Carriage::Carriage(DCMotor dcMotor, int hallSensorBottomPin, int hallSensorMiddlePin, int hallSensorTopPin) : Carriage()
{
	this->dcMotor = dcMotor;
	this->hallSensorBottomPin = hallSensorBottomPin;
	this->hallSensorMiddlePin = hallSensorMiddlePin;
	this->hallSensorTopPin = hallSensorTopPin;
}

Carriage::~Carriage()
{
}

void Carriage::HandleDCMotor(int speed, int goToHallSensor)
{
	bool motorTurnedOn = false;
	this->GetDCMotor().SetSpeed(speed);

	// If the carriage on the right height do nothing.
	if (digitalRead(goToHallSensor) == LOW)
	{
		// Turn the motor on with the correct direction based on the current position.
		switch (goToHallSensor)
		{
			case HALL_CARRIAGE_BOTTOM:
				if (digitalRead(this->hallSensorMiddlePin) == HIGH || digitalRead(this->hallSensorTopPin)  == HIGH)
				{
					motorTurnedOn = true;
					this->GetDCMotor().Start(DirectionType::Reverse);
				}
				break;
			case HALL_CARRIAGE_MIDDLE:
				if (digitalRead(this->hallSensorBottomPin) == HIGH)
				{
					motorTurnedOn = true;
					this->GetDCMotor().Start(DirectionType::Reverse);
				}
				else if (digitalRead(this->hallSensorTopPin) == HIGH)
				{
					motorTurnedOn = true;
					this->GetDCMotor().Start(DirectionType::Forward);
				}
				break;
			case HALL_CARRIAGE_TOP:
				if (digitalRead(this->hallSensorBottomPin) == HIGH || digitalRead(this->hallSensorMiddlePin) == HIGH)
				{
					motorTurnedOn = true;
					this->GetDCMotor().Start(DirectionType::Forward);
				}
				break;
			default:
				break;
		}
	}
	
	// When the carriage is not yet at the right height and a motor was turned on, make the DC motor spin indefinitely until we get a output from the sensor.
	// The sensor output is either LOW = 0 (false) or HIGH = 1 (true).
	while (digitalRead(goToHallSensor) == LOW && motorTurnedOn)
	{
		this->GetDCMotor().Run();
	}
	
	// Stop the DC motor after reaching the destination.
	this->GetDCMotor().Stop();
}

DCMotor Carriage::GetDCMotor()
{
	return this->dcMotor;
}

#include "Carriage.h"
#include "TominatorPins.h"

Carriage::Carriage()
{
}

Carriage::Carriage(DCMotor* dcMotor, int hallSensorBottomPin, int hallSensorMiddlePin, int hallSensorTopPin) : Carriage()
{
	this->dcMotor = dcMotor;
	this->hallSensorBottomPin = hallSensorBottomPin;
	this->hallSensorMiddlePin = hallSensorMiddlePin;
	this->hallSensorTopPin = hallSensorTopPin;
}

Carriage::~Carriage()
{
}

void Carriage::HandleDCMotor(int speedPercentage, int goToHallSensor)
{
	bool motorTurnedOn = false;
	this->GetDCMotor()->SetSpeedInPercentage(speedPercentage);

	Serial.print("bottom sensor: ");
	Serial.println(digitalRead(this->hallSensorBottomPin));
	Serial.print("middle sensor: ");
	Serial.println(digitalRead(this->hallSensorMiddlePin));
	Serial.print("top sensor: ");
	Serial.println(digitalRead(this->hallSensorTopPin));

	// If the carriage on the right height do nothing.
	if (digitalRead(goToHallSensor) == LOW)
	{
		// Turn the motor on with the correct direction based on the current position.
		switch (goToHallSensor)
		{
			case HALL_CARRIAGE_BOTTOM:
				motorTurnedOn = true;
				this->GetDCMotor()->Start(DirectionType::Reverse);
				break;
			case HALL_CARRIAGE_MIDDLE:
				if (digitalRead(this->hallSensorBottomPin) == LOW && digitalRead(this->hallSensorTopPin))
				{
					motorTurnedOn = true;
					this->GetDCMotor()->Start(DirectionType::Reverse);
				}
				else if (digitalRead(this->hallSensorTopPin) == LOW && digitalRead(this->hallSensorBottomPin))
				{
					motorTurnedOn = true;
					this->GetDCMotor()->Start(DirectionType::Forward);
				}
				else
				{
					motorTurnedOn = true;
					this->GetDCMotor()->Start(DirectionType::Reverse);
				}
				break;
			case HALL_CARRIAGE_TOP:
				if (digitalRead(this->hallSensorBottomPin) == LOW || digitalRead(this->hallSensorMiddlePin) == LOW)
				{
					motorTurnedOn = true;
					this->GetDCMotor()->Start(DirectionType::Forward);
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
		this->GetDCMotor()->Run();
	}
	
	// Stop the DC motor after reaching the destination.
	this->GetDCMotor()->Stop();
}


void Carriage::Home()
{	
	this->GetDCMotor()->Start(DirectionType::Reverse);
	this->GetDCMotor()->SetSpeedInPercentage(100);
	
	while (true)
	{
		// If the homing pin is HIGH then we successfully managed to return back to the default position.
		if (digitalRead(this->hallSensorBottomPin))
		{
			break;
		}
		else if (digitalRead(this->hallSensorBottomPin) == LOW)
		{
			this->GetDCMotor()->Run();
		}
	}
	
	this->GetDCMotor()->Stop();
}

DCMotor* Carriage::GetDCMotor()
{
	return this->dcMotor;
}

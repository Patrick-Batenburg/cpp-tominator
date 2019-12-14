#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor()
{
}

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin)
{
	this->triggerPin = triggerPin;
	this->echoPin = echoPin;
	pinMode(triggerPin, INPUT);
	pinMode(echoPin, INPUT);
}

UltrasonicSensor::~UltrasonicSensor()
{
}

int UltrasonicSensor::GetTriggerPin()
{
	return this->triggerPin;
}

int UltrasonicSensor::GetEchoPin()
{
	return this->echoPin;
}

#include "WaterBalloon.h"

WaterBalloon::WaterBalloon()
{
	this->type = WaterBalloonType::Empty;
	this->weight = 0;
}

WaterBalloon::WaterBalloon(WaterBalloonType type) : WaterBalloon()
{
	this->type = type;
}

WaterBalloon::WaterBalloon(float weight) : WaterBalloon()
{
	this->weight = weight;
	this->CalculateType();
}

WaterBalloon::WaterBalloon(WaterBalloonType type, float weight)
{
	this->type = type;
	this->weight = weight;
}

WaterBalloon::~WaterBalloon()
{
}

void WaterBalloon::CalculateType()
{
	if (this->weight >= (float)0.5 && this->weight <= (float)1.250)
	{
		this->SetType(WaterBalloonType::Small);
	}
	else if (this->weight >= (float)1.250 && this->weight <= (float)1.750)
	{
		this->SetType(WaterBalloonType::Medium);
	}
	else if (this->weight >= (float)1.750 && this->weight <= (float)10.000)
	{
		this->SetType(WaterBalloonType::Large);
	}
	else
	{
		this->SetType(WaterBalloonType::Unkown);
	}
}

float WaterBalloon::GetWeight()
{
	return this->weight;
}

void WaterBalloon::SetWeight(float value)
{
	this->weight = value;
	this->CalculateType();
}

WaterBalloonType WaterBalloon::GetType()
{
	return this->type;
}

void WaterBalloon::SetType(WaterBalloonType value)
{
	this->type = value;
}

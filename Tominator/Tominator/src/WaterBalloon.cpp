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
	if (this->weight >= 800 && this->weight <= 1200)
	{
		this->SetType(WaterBalloonType::Small);
	}
	else if (this->weight >= 1300 && this->weight <= 1700)
	{
		this->SetType(WaterBalloonType::Medium);
	}
	else if (this->weight >= 1800 && this->weight <= 2200)
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

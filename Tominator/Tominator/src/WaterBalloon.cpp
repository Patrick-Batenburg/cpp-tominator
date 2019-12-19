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
}

WaterBalloon::WaterBalloon(WaterBalloonType type, float weight)
{
	this->type = type;
	this->weight = weight;
}

WaterBalloon::~WaterBalloon()
{
}

float WaterBalloon::GetWeight()
{
	return this->weight;
}

void WaterBalloon::SetWeight(float value)
{
	this->weight = value;

	if (value >= 0.8 && value <= 1.2)
	{
		this->SetType(WaterBalloonType::Small);
	}
	else if (value >= 1.3 && value <= 1.7)
	{
		this->SetType(WaterBalloonType::Medium);
	}
	else if (value >= 1.8 && value <= 2.2)
	{
		this->SetType(WaterBalloonType::Large);
	}
	else
	{
		this->SetType(WaterBalloonType::Unkown);
	}
}

WaterBalloonType WaterBalloon::GetType()
{
	return this->type;
}

void WaterBalloon::SetType(WaterBalloonType value)
{
	this->type = value;
}

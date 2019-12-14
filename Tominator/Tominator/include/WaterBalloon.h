#pragma once

/**
	Types of water balloons.
*/
enum WaterBalloonType
{
	Empty,
	Small,
	Medium,
	Large,
	Unkown
};

class WaterBalloon
{
private:
	enum WaterBalloonType type;
	float weight;

public:
	/**
		Initializes a new instance of the WaterBalloon class.
	*/
	WaterBalloon();
		
	/**
		Initializes a new instance of the WaterBalloon class.

		@param type The water balloon's type.
	*/
	WaterBalloon(WaterBalloonType type);	
	
	/**
		Initializes a new instance of the WaterBalloon class.

		@param weight The water balloon's weight.
	*/
	WaterBalloon(float weight);
	
	/**
		Initializes a new instance of the WaterBalloon class.

		@param type The water balloon's type.
		@param weight The water balloon's weight.
	*/
	WaterBalloon(WaterBalloonType type, float weight);

	/**
		Deconstruct the instance of the WaterBalloon class.
	*/
	~WaterBalloon();
	
	/**
		Gets the water balloon's weight.

		@return The water balloon's weight.
	*/
	float GetWeight();
	
	/**
		Sets the water balloon's weight.

		@param value The water balloon's weight.
	*/
	void SetWeight(float value);
	
	/**
		Gets the water balloon's type.

		@return The water balloon's type.
	*/
	WaterBalloonType GetType();
	
	/**
		Sets the water balloon's type.

		@param value The water balloon's type.
	*/
	void SetType(WaterBalloonType value);
};

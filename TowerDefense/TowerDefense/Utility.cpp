#include "Utility.h"

using namespace utils;


float utils::calculateRotation(const sf::Vector2f & first, const sf::Vector2f & second)
{
	float dx = first.x - second.x;
	float dy = first.y - second.y;
	float rotation = ((atan2(dy, dx)) * 180 / PI) + 180;

	return rotation;
}

float utils::calculateDistance(const sf::Vector2f & first, const sf::Vector2f & second)
{
	return sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2));
}

float utils::mod(float a, float b)
{
	return fmod((fmod(a, b) + b), b);
}

float utils::shortestRotation(float sourceAngle, float targetAngle)
{
	float a = mod((sourceAngle - targetAngle), 360.f);
	float b = mod((targetAngle - sourceAngle), 360.f);
	
	return  (a < b ? -a : b);
}

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

namespace utils
{
	const float PI = 3.14159265;

	float calculateRotation(const sf::Vector2f &first, const sf::Vector2f &second);

	float calculateDistance(const sf::Vector2f &first, const sf::Vector2f &second);

	float mod(float a, float b);

	float shortestRotation(float sourceAngle, float targetAngle);
}
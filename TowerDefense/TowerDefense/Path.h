#pragma once
#include <SFML\Graphics.hpp>
#include "tmxlite\Map.hpp"



class Path
{
	
public:
	std::vector<sf::Vector2f> mPolyline;

	void loadFromTmx(const tmx::Map &map);
};


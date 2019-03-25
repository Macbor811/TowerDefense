#include "Path.h"
#include <iostream>

void Path::loadFromTmx(const tmx::Map &map)
{
	auto &lays = map.getLayers();
	for (auto &element : lays)
	{
		if (element->getName() == "Navigation")
		{
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(element.get())->getObjects();
			for (const auto& object : objects)
			{
				const auto& points = object.getPoints();
				const auto& offset = object.getPosition();
				for(auto &element : points)
				{
					mPolyline.push_back(sf::Vector2f(element.x + offset.x, element.y + offset.y));
				}
			}
		}
	}
}

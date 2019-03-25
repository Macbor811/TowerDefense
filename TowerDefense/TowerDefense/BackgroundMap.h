#pragma once
#include <string>
#include "SceneNode.h"
#include "SFMLOrthogonalLayer.hpp"
#include "tmxlite\Map.hpp"

class BackgroundMap : public SceneNode
{
	const tmx::Map &mCurrentMap;
	std::vector<std::unique_ptr<MapLayer>> mDrawableLayers;

public:

	BackgroundMap(const tmx::Map & tmx);


	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;


};


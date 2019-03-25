#include "BackgroundMap.h"



BackgroundMap::BackgroundMap(const tmx::Map & tmx) : mCurrentMap(tmx)
{
	const auto &tmxLayers = mCurrentMap.getLayers();

	int i = 0;
	for (const auto& element : tmxLayers)
	{
		if (element->getType() == tmx::Layer::Type::Tile)
		{
			mDrawableLayers.emplace_back(new MapLayer(mCurrentMap, i));
		}
		i++;
	}
}


void BackgroundMap::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto &layer : mDrawableLayers)
	{
		target.draw(*layer, states);
	}
	
}

#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include <memory>

namespace Textures
{
	enum class ID 
	{ 
		Slot, 
		TowerRegular, 
		TowerSplash, 
		ProjectileRegular,
		ProjectileSplash,
		EnemySoldier, 
		EnemyTank, 
		EnemySupersoldier ,
		Button,
		ButtonRightArrow,
		ButtonLeftArrow
	};
}


class TextureHolder
{
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;

public:
	void load(Textures::ID id, const std::string& filename);
	
	sf::Texture& get(Textures::ID id);
	const sf::Texture& get(Textures::ID id) const;
};


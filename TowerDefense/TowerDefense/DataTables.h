#pragma once
#include "TextureHolder.h"
#include "Path.h"
#include <SFML\System\Time.hpp>

namespace EnemyType
{
	enum Type
	{
		Soldier,
		Tank,
		Supersoldier,
		Count
	};
}


namespace TowerType
{
	enum Type
	{
		Regular,
		Splash,
		Count
	};
}


namespace ProjectileType
{
	enum Type
	{
		Regular,
		Splash,
		Count
	};
}


struct EnemyData
{
	float velocity;
	int hitpoints;
	int money;
	int playerDmg;
	Textures::ID texture;
};

struct ProjectileData
{
	float velocity;
	int damage;	
	Textures::ID texture;
	float range;
};

struct TowerData
{	
	float range;
	Textures::ID texture;
	sf::Time reloadTime;
	int cost;
	ProjectileData projectileData;
};


EnemyType::Type stringToEnum(const std::string & name);

EnemyData getEnemyData(EnemyType::Type type);

ProjectileData initializeProjectileData(ProjectileType::Type type);

TowerData getTowerData(TowerType::Type type);


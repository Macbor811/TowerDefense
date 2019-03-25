#include "DataTables.h"
#include <string>




EnemyType::Type stringToEnum(const std::string &name)
{
	if (name == "Soldier") return EnemyType::Soldier;
	else if (name == "Supersoldier") return EnemyType::Supersoldier;
	else if (name == "Tank") return EnemyType::Tank;
}



EnemyData getEnemyData(EnemyType::Type type)
{
	EnemyData data;
	switch (type)
	{
	case EnemyType::Soldier:		
	{
		
		data.hitpoints = 3;
		data.velocity = 80;
		data.money = 5;
		data.playerDmg = 1;
		data.texture = Textures::ID::EnemySoldier;
		break;
	}
	case EnemyType::Tank:
	{
		data.hitpoints = 18;
		data.velocity = 50;
		data.money = 40;
		data.playerDmg = 3;
		data.texture = Textures::ID::EnemyTank;
		break;
	}
	case EnemyType::Supersoldier:
	{
		data.hitpoints = 9;
		data.velocity = 80;
		data.money = 15;
		data.playerDmg = 2;
		data.texture = Textures::ID::EnemySupersoldier;
		break;
	}
	}
	return data;
}

ProjectileData initializeProjectileData(ProjectileType::Type type)
{
	return ProjectileData();
}

TowerData getTowerData(TowerType::Type type)
{
	TowerData data;
	switch (type)
	{
	case TowerType::Regular:
		data.range = 200;
		data.reloadTime = sf::seconds(0.5);
		data.cost = 15;
		data.texture = Textures::ID::TowerRegular;
		data.projectileData.damage = 1;
		data.projectileData.velocity = 700;
		data.projectileData.texture = Textures::ID::ProjectileRegular;
		data.projectileData.range = data.range;
		break;
	case TowerType::Splash:
		data.range = 150;
		data.reloadTime = sf::seconds(1);
		data.cost = 20;
		data.texture = Textures::ID::TowerSplash;
		data.projectileData.damage = 2;
		data.projectileData.velocity = 500;
		data.projectileData.texture = Textures::ID::ProjectileSplash;
		data.projectileData.range = data.range;
		break;
	}
	return data;
}



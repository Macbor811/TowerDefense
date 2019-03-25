#pragma once
#include <string>
#include <sstream>
#include "SceneNode.h"
#include "DataTables.h"

//#include <SFML\System\NonCopyable.hpp> 

class PlayerData : public SceneNode
{
	int mHitpoints = 10;
	int mMoney = 30;
	TowerType::Type mSelectedTowerType = TowerType::Regular;

public:
	int addMoney(int value);

	int pay(int value);

	int takeDamage(int damage);

	int getHP();

	std::string printMoney() const;

	int getMoney() const;

	std::string printHitpoints() const;

	unsigned int getCategory() const override;

	TowerType::Type getSelectedTowerType() const;

	void setSelectedTowerType(TowerType::Type type);

};


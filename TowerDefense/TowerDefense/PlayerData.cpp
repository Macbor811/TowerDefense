#include "PlayerData.h"
#include "GameEvent.h"



int PlayerData::addMoney(int value)
{
	mMoney += value;
	return mMoney;
}
int PlayerData::pay(int value)
{
	mMoney -= value;
	return mMoney;
}
int PlayerData::takeDamage(int damage)
{
	mHitpoints -= damage;
	if (mHitpoints <= 0)
	{
		GameEvent gameEvent;
		gameEvent.type = (GameEvent::Type::GameLost);
		pushGameEvent(gameEvent);
	}
	return mHitpoints;
}

int PlayerData::getHP()
{
	return mHitpoints;
}

std::string PlayerData::printMoney() const
{
	std::stringstream ss;
	ss << mMoney << "$" << std::endl;
	return ss.str();
}
int PlayerData::getMoney() const
{
	return mMoney;
}
std::string PlayerData::printHitpoints() const
{
	std::stringstream ss;
	ss << mHitpoints << " HP" << std::endl;
	return ss.str();
}

unsigned int PlayerData::getCategory() const
{
	return ReceiverCategory::Player;
}

TowerType::Type PlayerData::getSelectedTowerType() const
{
	return mSelectedTowerType;
}

void PlayerData::setSelectedTowerType(TowerType::Type type)
{
	mSelectedTowerType = type;
}



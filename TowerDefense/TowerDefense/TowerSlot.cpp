#include "TowerSlot.h"
#include "Tower.h"
#include <iostream>

TowerSlot::TowerSlot(const sf::RectangleShape & slot, const TextureHolder& textures, const sf::RenderWindow &window,
	SceneNode &projectileLayer, PlayerData & player) :
	 mTextures(textures), mWindow(window), 
	mSlot(textures.get(Textures::ID::Slot)), 
	mIsBuilt(false), 
	mProjectileLayer(projectileLayer), 
	mPlayer(player)
{
	sf::FloatRect bounds = slot.getGlobalBounds();
	
	mSlot.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	setPosition(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);	
	mSlot.setColor(sf::Color::Transparent);

	mRangeCircle.setFillColor(sf::Color::Transparent);
	mRangeCircle.setRadius(getTowerData(TowerType::Regular).range);
	mRangeCircle.setPosition(getLevelPosition());
	sf::FloatRect circleBounds = mRangeCircle.getGlobalBounds();
	mRangeCircle.setOrigin(circleBounds.left + circleBounds.width / 2.f, circleBounds.top + circleBounds.height / 2.f);
	
}

void TowerSlot::buildTowerIfClicked()
{
	const auto globalBounds = getLevelTransform().transformRect(mSlot.getGlobalBounds());
	if (!mIsBuilt && globalBounds.contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))))
	{
		std::unique_ptr<Tower> tower(new Tower(mPlayer.getSelectedTowerType(), mTextures, mWindow, mProjectileLayer));
		if (mPlayer.getMoney() >= tower->getCost())
		{
			mPlayer.pay(tower->getCost());
			mIsBuilt = true;
			attachChild(std::move(tower));
		}
	}
}

void TowerSlot::updateRangePreview()
{
	mRangeCircle.setOrigin(0, 0);
	mRangeCircle.setRadius(getTowerData(mPlayer.getSelectedTowerType()).range);
	sf::FloatRect circleBounds = mRangeCircle.getGlobalBounds();
	mRangeCircle.setOrigin(circleBounds.left + circleBounds.width / 2.f, circleBounds.top + circleBounds.height / 2.f);
}

void TowerSlot::updateCurrent(sf::Time dt, CommandQueue &commands)
{	
	const auto globalBounds = getLevelTransform().transformRect(mSlot.getGlobalBounds());
	if (!mIsBuilt && globalBounds.contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))))
	{
		mRangeCircle.setFillColor(sf::Color(255, 255, 255, 30));
	}
	else
		mRangeCircle.setFillColor(sf::Color::Transparent);
}




void TowerSlot::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSlot, states);
	target.draw(mRangeCircle, states);
}

unsigned int TowerSlot::getCategory() const
{
	return ReceiverCategory::TowerSlot;
}



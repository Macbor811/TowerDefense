#include "HUD.h"



HUD::HUD(const sf::Font & font, const PlayerData & player) :
	mFont(font),
	mPlayer(player)
{
	std::unique_ptr<TextNode> moneyDisplay(std::make_unique<TextNode>(font, mPlayer.printMoney()));
	moneyDisplay->setPosition(sf::Vector2f( 0, 0));
	mMoneyDisplay = moneyDisplay.get();
	moneyDisplay->setTextOutlineThickness(1.5);
	attachChild(std::move(moneyDisplay));
	
	std::unique_ptr<TextNode> hpDisplay(std::make_unique<TextNode>(font, mPlayer.printHitpoints()));
	hpDisplay->setPosition(mMoneyDisplay->getLevelPosition().x, mMoneyDisplay->getLevelPosition().y + 30);
	mHPDisplay = hpDisplay.get();
	hpDisplay->setTextOutlineThickness(1.5);
	attachChild(std::move(hpDisplay));
	


	mSelectedTower.setPosition(0, 896);
	mSelectedTowerRect.setFillColor(sf::Color(255,255,255, 100));
	mSelectedTowerRect.setPosition(mSelectedTower.getPosition());

	std::unique_ptr<TextNode> costDisplay(std::make_unique<TextNode>(font, ""));
	costDisplay->setTextOutlineThickness(1.5);
	costDisplay->centerOrigin();
	costDisplay->setPosition(mSelectedTower.getPosition().x + 16, mSelectedTower.getPosition().y + 16);
	mCostDisplay = costDisplay.get();
	attachChild(std::move(costDisplay));
}

void  HUD::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSelectedTowerRect, states);
	target.draw(mSelectedTower, states);	
}

void HUD::updateCurrent(sf::Time dt, CommandQueue &commands)
{
	mMoneyDisplay->setString(mPlayer.printMoney());
	mHPDisplay->setString(mPlayer.printHitpoints());
	if (mPlayer.getMoney() < getTowerData(mPlayer.getSelectedTowerType()).cost)
	{
		mSelectedTowerRect.setFillColor(sf::Color(255, 0, 0, 100));
	}
	else
	{
		mSelectedTowerRect.setFillColor(sf::Color(255, 255, 255, 100));
	}
}

void HUD::updateTowerDisplay(const TextureHolder &textures)
{
	mSelectedTower.setTexture(textures.get(getTowerData(mPlayer.getSelectedTowerType()).texture));
	mSelectedTowerRect.setSize(sf::Vector2f(mSelectedTower.getLocalBounds().height, mSelectedTower.getLocalBounds().width));
	mCostDisplay->setString(std::to_string(getTowerData(mPlayer.getSelectedTowerType()).cost) + "$");
}

unsigned int HUD::getCategory() const
{
	return ReceiverCategory::HUD;
}

#pragma once
#include "SceneNode.h"
#include "TextNode.h"
#include "PlayerData.h"
#include <array>
#include "DataTables.h"
#include "TextureHolder.h"


class HUD : public SceneNode
{
	const sf::Font &mFont;
	const PlayerData &mPlayer;
	
	TextNode * mMoneyDisplay;
	TextNode * mHPDisplay;
	TextNode * mCostDisplay;

	sf::Sprite mSelectedTower;
	sf::RectangleShape mSelectedTowerRect;

	int mWaveNumber = 0;

public:
	HUD(const sf::Font &font, const PlayerData &player);
	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
	void updateCurrent(sf::Time dt, CommandQueue &commands);
	void updateTowerDisplay(const TextureHolder &textures);
	unsigned int getCategory() const override;
};


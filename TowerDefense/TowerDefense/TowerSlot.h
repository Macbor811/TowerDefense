#pragma once
#include "SceneNode.h"
#include "Tower.h"
#include "PlayerData.h"

class TowerSlot : public SceneNode
{
	
	const TextureHolder& mTextures;
	const sf::RenderWindow &mWindow;
	sf::Sprite mSlot;
	bool mIsBuilt;
	SceneNode &mProjectileLayer;
	PlayerData &mPlayer;
	sf::CircleShape mRangeCircle;

public:
	
	TowerSlot::TowerSlot(const sf::RectangleShape & slot, const TextureHolder& textures, const sf::RenderWindow &window,
		SceneNode &projectileLayer, PlayerData & player);

	void buildTowerIfClicked();

	void updateRangePreview();

	void updateCurrent(sf::Time dt, CommandQueue &commands);

	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

	unsigned int getCategory() const override;
};


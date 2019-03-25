#pragma once
#include "SceneNode.h"
#include "TextureHolder.h"
#include "Enemy.h"
#include <vector>




class Tower : public SceneNode
{
	TowerData mData;
	const TextureHolder& mTextures;
	sf::Sprite mSprite;
	sf::CircleShape mRangeCircle;

	const sf::RenderWindow &mWindow;
	sf::Time mElapsedReloadTime = sf::Time::Zero;

	SceneNode &mProjectileLayer;
	Enemy * mTarget = nullptr;
	float mTargetRotation = 0;

public:

	Tower::Tower(TowerType::Type type, const TextureHolder& textures, const sf::RenderWindow &window, SceneNode &projectileLayer);

	//void build(Textures::ID id);

	void rotateToTarget(sf::Vector2f target);

	void updateCurrent(sf::Time dt, CommandQueue &commands);
	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

	void setTarget(Enemy * target);
	
	float getRange() const;

	int getCost() const;

	bool hasInRange(const Enemy & target) const;
};



#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "DataTables.h"

class Projectile : public Entity
{

	sf::Sprite mSprite;
	float mRotation;
	bool mIsDestroyed = false;
	ProjectileData mData;
	float mTraveledDistance = 0.f;
public:
	

	Projectile(const ProjectileData &data, const TextureHolder & textures);

	void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

	void updateCurrent(sf::Time dt, CommandQueue &commands);

	sf::FloatRect getBoundingRect() const override;

	void markForRemoval() override;

	bool isMarkedForRemoval() const override;

	int causeDamage() const;

};


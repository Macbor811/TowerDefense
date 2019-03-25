#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "Path.h"
#include "DataTables.h"



class Enemy : public Entity
{
	struct NavigationData
	{
		const Path &path;
		int lastPathPointIndex;
		float prevDistance;

		NavigationData(const Path & pathPtr, float distance) : path(pathPtr), lastPathPointIndex(0), prevDistance(distance)
		{}
	};

	sf::Sprite mSprite;
	//sf::RectangleShape mHealthbar;
	
	NavigationData mNavData;

	EnemyData mData;

	bool mIsDestroyed = false;

	float mProgress = 0;

	float mTargetRotation;

private:
	void rotateToTarget(sf::Vector2f targetPos);
	void whenReachedEnd(CommandQueue &commands);
public:
	Enemy::Enemy(EnemyType::Type type, const TextureHolder& textures, const Path & path);

	void updateCurrent(sf::Time dt, CommandQueue & commands);
	bool isDestroyed() const;
	void markForRemoval() override;
	bool isMarkedForRemoval() const override;
	sf::FloatRect getBoundingRect() const override;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void takeDamage(float dmg);

	float getProgress() const { return mProgress; };
	int dropMoney();
};


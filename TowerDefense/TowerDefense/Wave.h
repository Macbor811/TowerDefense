#pragma once
#include "Enemy.h"
#include <queue>

class Wave : public SceneNode
{
	
	sf::Time mElapsedSpawnTime;
	sf::Time mInterval;
	std::queue<std::unique_ptr<Enemy>> mEnemies;
	bool hasEnded = false;

public:
		
	Wave(float spawnInterval);

	void updateCurrent(sf::Time dt, CommandQueue &commands);
	void insertEnemies(int count, EnemyType::Type type, const TextureHolder & textures, const Path & path);
	void markForRemoval() override;
	bool isMarkedForRemoval() const override;
};


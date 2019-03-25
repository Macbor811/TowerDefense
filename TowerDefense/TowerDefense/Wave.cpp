#include "Wave.h"
#include "DataTables.h"
#include "HUD.h"

Wave::Wave(float spawnInterval) : mInterval(sf::seconds(spawnInterval))
{
}

void Wave::updateCurrent(sf::Time dt, CommandQueue &commands)//, SceneNode & sceneGraph)
{
	mElapsedSpawnTime += dt;
	if (mElapsedSpawnTime >= mInterval && !mEnemies.empty())
	{		
		attachChild(std::move(mEnemies.front()));
		mEnemies.pop();
		mElapsedSpawnTime = sf::Time::Zero;
	}
	else if (mEnemies.empty() && getChildren().empty())
	{
		markForRemoval();
	}
}


void Wave::insertEnemies(int count, EnemyType::Type type, const TextureHolder &textures, const Path &path)
{
	for (int i = 0; i < count; i++)
	{
		std::unique_ptr<Enemy> soldier(new Enemy(type, textures, path));
		mEnemies.push(std::move(soldier));
	}
}

void Wave::markForRemoval()
{
	hasEnded = true;
}

bool Wave::isMarkedForRemoval() const
{
	return hasEnded;
}

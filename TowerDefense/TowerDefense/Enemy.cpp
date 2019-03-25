#include "Enemy.h"
#include "Utility.h"
#include <iostream>
#include "Projectile.h"
#include "PlayerData.h"

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Enemy::takeDamage(float dmg)
{
	mData.hitpoints -= dmg;
	if (mData.hitpoints <= 0)
		markForRemoval();
}

int Enemy::dropMoney()
{
	if (isMarkedForRemoval())
		return mData.money;
	else
		return 0;
}

Enemy::Enemy(EnemyType::Type type, const TextureHolder& textures, const Path & path) :
	mData(getEnemyData(type)),
	mNavData(path, utils::calculateDistance(path.mPolyline[0], path.mPolyline[1]) + 1)	
{

	mSprite.setTexture(textures.get(mData.texture));
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	mSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	setPosition(mNavData.path.mPolyline[0]);

	setRotation(utils::calculateRotation(getLevelPosition(), mNavData.path.mPolyline[1]));
	mTargetRotation = utils::calculateRotation(getLevelPosition(), mNavData.path.mPolyline[1]);
	setVelocity(mData.velocity);

}

void Enemy::rotateToTarget(sf::Vector2f targetPos)
{
	sf::Vector2f pos(getLevelPosition());
	mTargetRotation = (utils::calculateRotation(pos, targetPos));
	if (getRotation() != mTargetRotation)
	{
		const float delta = utils::shortestRotation(getRotation(), mTargetRotation);
		if (fabs(delta) < 1)
			setRotation(mTargetRotation);
		else
			rotate(delta > 0 ? 1.5 : -1.5);
	}
}

void Enemy::whenReachedEnd(CommandQueue &commands)
{
	Command damagePlayer;
	damagePlayer.category = ReceiverCategory::Player;
	int dmg = mData.playerDmg;
	damagePlayer.action = derivedAction<PlayerData>([=](PlayerData & player, sf::Time)
	{
		player.takeDamage(dmg);
	});
	commands.push(damagePlayer);
	mIsDestroyed = true;
}

void Enemy::updateCurrent(sf::Time dt, CommandQueue &commands)
{	
	float currentDistance = utils::calculateDistance(getLevelPosition(), mNavData.path.mPolyline[mNavData.lastPathPointIndex + 1]);
	sf::Vector2f offset = getVelocityVector() * dt.asSeconds();
	
	mProgress += utils::calculateDistance(getLevelPosition(), getLevelPosition() + offset);

	if (currentDistance == 0 || mNavData.prevDistance - currentDistance <= 0)
	{
		mNavData.lastPathPointIndex++;
		if (mNavData.lastPathPointIndex + 1 == mNavData.path.mPolyline.size()) //|| mIsDestroyed)
		{
			whenReachedEnd(commands);
			return;
		}
		mNavData.prevDistance = utils::calculateDistance(getLevelPosition(), mNavData.path.mPolyline[mNavData.lastPathPointIndex + 1]);
	}
	else 
		mNavData.prevDistance = currentDistance;
	rotateToTarget(mNavData.path.mPolyline[mNavData.lastPathPointIndex + 1]);
	move(offset);
	
}

bool Enemy::isDestroyed() const
{
	return mIsDestroyed;
}

void Enemy::markForRemoval()
{
	mIsDestroyed = true;
}

bool Enemy::isMarkedForRemoval() const
{
	return isDestroyed();
}

sf::FloatRect Enemy::getBoundingRect() const
{
	return getLevelTransform().transformRect(mSprite.getGlobalBounds());
}
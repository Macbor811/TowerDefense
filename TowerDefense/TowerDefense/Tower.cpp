#include "Tower.h"
#include "Projectile.h"
#include "Utility.h"
#include <iostream>

Tower::Tower(TowerType::Type type, const TextureHolder& textures, const sf::RenderWindow &window, SceneNode &projectileLayer) :
	mTextures(textures),
	mWindow(window), 
	mData(getTowerData(type)),
	mProjectileLayer(projectileLayer)
{
	mSprite.setTexture(mTextures.get(mData.texture), true);
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	mSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f + 8.f);

	mRangeCircle.setFillColor(sf::Color::Transparent);
	mRangeCircle.setRadius(mData.range);
	mRangeCircle.setPosition(getLevelPosition());
	sf::FloatRect circleBounds = mRangeCircle.getGlobalBounds();
	mRangeCircle.setOrigin(circleBounds.left + circleBounds.width / 2.f, circleBounds.top + circleBounds.height / 2.f);
}


void Tower::rotateToTarget(sf::Vector2f targetPos)
{
	sf::Vector2f pos(getLevelPosition());
	mTargetRotation = (utils::calculateRotation(pos, targetPos) + 90.f);
	if (getRotation() != mTargetRotation)
	{
		const float delta = utils::shortestRotation(getRotation(), mTargetRotation);
		if (fabs(delta) < 1)
			setRotation(mTargetRotation);
		else
			rotate(delta > 0 ? 0.5 : -0.5);
	}
}

void Tower::updateCurrent(sf::Time dt, CommandQueue &commands)
{
	mElapsedReloadTime += dt;
	if (mTarget)
	{
		sf::Vector2f enemyPos(mTarget->getLevelPosition().x, mTarget->getLevelPosition().y);//(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)));//
		rotateToTarget(enemyPos);

		if (mElapsedReloadTime >= mData.reloadTime)
		{
			mElapsedReloadTime = sf::Time::Zero;

			std::unique_ptr<Projectile> projectile(new Projectile(mData.projectileData, mTextures));
			projectile->setRotation(getRotation() - 90.f);
			projectile->setPosition(getLevelPosition());

			mProjectileLayer.attachChild(std::move(projectile));

		}
	}
	const auto globalBounds = getLevelTransform().transformRect(mSprite.getGlobalBounds());

	if (globalBounds.contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))))
		mRangeCircle.setFillColor(sf::Color(255, 255, 255, 30));
	else 
		mRangeCircle.setFillColor(sf::Color::Transparent);
}


void Tower::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
	target.draw(mRangeCircle, states);
}



void Tower::setTarget(Enemy * target)
{
	mTarget = target;
}

float Tower::getRange() const
{
	return mData.range;
}

int Tower::getCost() const
{
	return mData.cost;
}

bool Tower::hasInRange(const Enemy & target) const
{
	return utils::calculateDistance(getLevelPosition(), target.getLevelPosition()) < getRange();
}

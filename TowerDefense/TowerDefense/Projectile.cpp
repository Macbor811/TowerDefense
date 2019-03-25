#include "Projectile.h"
#include "Utility.h"


Projectile::Projectile(const ProjectileData &data, const TextureHolder & textures) :
	mData(data)
{
	mSprite.setTexture(textures.get(mData.texture));
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	
	setVelocity(mData.velocity);
}



void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue &commands)
{
	sf::Vector2f offset( getVelocityVector() * dt.asSeconds() );
	sf::Vector2f currentPos(getLevelPosition());
	mTraveledDistance += utils::calculateDistance(currentPos, currentPos + offset);
	if (mTraveledDistance > mData.range)
		markForRemoval();
	else
		move(offset);
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getLevelTransform().transformRect(mSprite.getGlobalBounds());
}

void Projectile::markForRemoval()
{
	mIsDestroyed = true;
}

bool Projectile::isMarkedForRemoval() const
{
	return mIsDestroyed;
}

int Projectile::causeDamage() const
{
	return mData.damage;
}


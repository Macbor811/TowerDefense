#include "Entity.h"
#include "Utility.h"


void Entity::setVelocity(float v)
{
	mVelocity = v;
}

float Entity::getVelocity() const
{
	return mVelocity;
}

sf::Vector2f Entity::getVelocityVector()
{
	return sf::Vector2f(cos(this->getRotation()*utils::PI / 180) * mVelocity, sin(this->getRotation()*utils::PI / 180) * mVelocity);
}



void Entity::updateCurrent(sf::Time dt, CommandQueue &commands)
{
	move(getVelocityVector() * dt.asSeconds());
}
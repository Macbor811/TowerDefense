#pragma once
#include "SceneNode.h"

class Entity : public SceneNode
{
	float mVelocity;
public:

	void setVelocity(float v);
	float getVelocity() const;
	sf::Vector2f getVelocityVector();
	

	bool isMarkedForRemoval() const { return false; };
private:
	
	virtual void updateCurrent(sf::Time dt, CommandQueue &commands);

};
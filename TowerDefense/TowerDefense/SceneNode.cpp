#include "SceneNode.h"
#include <cassert>
#include <functional>
#include <iostream>
#include "Utility.h"

void SceneNode::attachChild(NodePtr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	
	for (const NodePtr& child : mChildren)
	{
		child->draw(target, states);
	}
}

SceneNode::NodePtr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&node](NodePtr& p) -> bool { return p.get() == &node; });
	assert(found != mChildren.end());
	NodePtr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
	updateCurrent(dt, commands);
	updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time, CommandQueue&)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
	for(NodePtr & child : mChildren)
		child->update(dt, commands);
}

sf::Transform SceneNode::getLevelTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;
	return transform;
}

sf::Vector2f SceneNode::getLevelPosition() const
{
	return getLevelTransform() * sf::Vector2f();
}

const std::vector<std::unique_ptr<SceneNode>>& SceneNode::getChildren() const
{
	return mChildren;
}

bool SceneNode::isMarkedForRemoval() const
{
	return false;
}


void SceneNode::removeDestroyed()
{
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeDestroyed));
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	return sf::FloatRect(0, 0, 0, 0);
}

bool collision(const SceneNode& enemy, const SceneNode& projectile)
{
	// lhs.getBoundingRect().intersects(rhs.getBoundingRect());
	auto box = enemy.getBoundingRect();
	return box.contains(projectile.getLevelPosition());
	
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	if (command.category & getCategory())
		command.action(*this, dt);


	for (auto & child : mChildren)
		child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const
{
	return ReceiverCategory::Any;
}
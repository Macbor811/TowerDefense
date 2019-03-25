#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <memory>
#include "Command.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> NodePtr;
private:
	std::vector<NodePtr> mChildren;
	SceneNode* mParent;

public:

	void attachChild(NodePtr child);
	NodePtr detachChild(const SceneNode& node);
	void update(sf::Time dt, CommandQueue& commands);
	
	sf::Transform getLevelTransform() const;

	sf::Vector2f getLevelPosition() const;

	const std::vector<NodePtr>& getChildren() const;

	const SceneNode* getParent() const { return mParent; };

	virtual bool isMarkedForRemoval() const;

	virtual void markForRemoval() {};

	void removeDestroyed();

	virtual sf::FloatRect getBoundingRect() const;

	void onCommand(const Command & command, sf::Time dt);

	virtual unsigned int getCategory() const;


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}

	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	void updateChildren(sf::Time dt, CommandQueue& commands);




};

bool collision(const SceneNode & lhs, const SceneNode & rhs);

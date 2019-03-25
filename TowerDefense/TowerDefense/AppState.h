#pragma once
#include "TextureHolder.h"
#include "Command.h"
#include "SceneNode.h"

class AppState : private sf::NonCopyable
{
protected:
	sf::RenderWindow& mWindow;
	TextureHolder &mTextures;
	SceneNode mSceneGraph;
	CommandQueue mCommandQueue;

public:
	AppState(sf::RenderWindow& window, TextureHolder &textures) : mWindow(window), mTextures(textures) {};
	virtual void handleInput(const sf::Event & event) = 0;
	virtual void draw() = 0;
	virtual void update(sf::Time dt) = 0;

protected:
	virtual void loadAssets() = 0;
};


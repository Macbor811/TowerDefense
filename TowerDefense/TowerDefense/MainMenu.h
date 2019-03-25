#pragma once
#include <SFML\Graphics.hpp>
#include "AppState.h"
#include "SceneNode.h"
#include "TextureHolder.h"
#include "Button.h"

class MainMenu : public AppState
{
	sf::Font mFont;
	sf::RectangleShape mBackground;

public:
	Button * mPrevLevelButton;
	Button * mNextLevelButton;
	Button * mLevelButton;
	Button * mExitButton;
	TextNode * mSelectedLevelDisplay;

	MainMenu(sf::RenderWindow & window, TextureHolder & textures);

	virtual void draw() override;

	virtual void update(sf::Time dt) override;



private:

	void setupButtons();
	virtual void loadAssets() override;
	virtual void handleInput(const sf::Event & event) override;
};


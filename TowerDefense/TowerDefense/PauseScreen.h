#pragma once
#include "Button.h"
#include "AppState.h"
#include "Level.h"

class PauseScreen : public AppState
{
	Level * mLevel;
	sf::Font mFont;
	sf::RectangleShape mDarkBackground;

public:
	PauseScreen(sf::RenderWindow & window, TextureHolder & textures, Level *level);
	virtual void handleInput(const sf::Event & event) override;
	virtual void draw() override;
	virtual void update(sf::Time dt) override;

	Button * mExitButton;
	Button * mReturnToMenuButton;
	Button * mContinueButton;
	void setLevel(Level * level);
private:
	virtual void loadAssets() override;
};


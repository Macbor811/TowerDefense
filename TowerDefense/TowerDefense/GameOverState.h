#pragma once
#include "AppState.h"
#include "Level.h"
#include "Button.h"

class GameOverState : public AppState
{
	Level * mLevel;
	sf::Font mFont;
	sf::RectangleShape mDarkBackground;
	TextNode * mMessage;
public:
	GameOverState(sf::RenderWindow & window, TextureHolder & textures, Level *level, const std::string &message);

	virtual void handleInput(const sf::Event & event) override;

	void setMessage(const std::string & message);

	virtual void draw() override;

	virtual void update(sf::Time dt) override;



	Button * mExitButton;
	Button * mReturnToMenuButton;
	Button * mRestartButton;
	void setLevel(Level * level);
private:
	virtual void loadAssets() override;

};


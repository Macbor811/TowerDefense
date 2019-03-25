#pragma once
#include <SFML\Graphics.hpp>
#include "Level.h"
#include "PauseScreen.h"
#include "MainMenu.h"
#include "GameOverState.h"

class Game
{
	TextureHolder mTextures;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	const sf::Vector2u mViewSize = { 960, 960 };
	sf::RenderWindow mWindow;
	int mSelectedLevelIndex = 0;
	std::vector<std::pair<std::string, std::string>> mLevels;
	std::unique_ptr<Level> mCurrentLevel;
	PauseScreen mPauseScreen;
	MainMenu mMainMenu;
	GameOverState mGameOverState;
	AppState * mCurrentState;
	sf::RectangleShape mBlackRect;
	//bool mIsPaused = false;

public:

	Game();
	void setMainMenuCallbacks();
	void setPauseScreenCallbacks();
	void setGameOverStateCallbacks();

	void startSelectedLevel();
	void returnToMenu();
	void run();

private:
	void processEvents();
	void onResize(const sf::Event & event);
	void update(sf::Time deltaTime);
	void render();
	void loadLevelsList(const std::string &filename);
	//void render();


};

#pragma once
#include <SFML\Graphics.hpp>
#include <array>
#include <queue>
#include <string>
#include "AppState.h"
#include "TextureHolder.h"
#include "SceneNode.h"
#include "BackgroundMap.h"
#include "Enemy.h"
#include "Path.h"
#include "PlayerData.h"
#include "Command.h"
#include "Wave.h"

class Level :  public AppState
{
	struct Stats
	{
		int enemiesKilled = 0;
		int hits = 0;
		sf::Time time = sf::Time::Zero;
	};
	enum Layer
	{
		Background,
		LandEnemies,
		Projectiles,
		Towers,		
		AirEnemies,
		HUDLayer,
		LayerCount
	};

	std::vector<Path> mPaths;
	tmx::Map mTmx;
	std::array<SceneNode*, Layer::LayerCount> mSceneLayers;

	sf::Clock mClock;
	PlayerData mPlayer;
	sf::Text mouseCoordsText;
	sf::Font font;

	
	std::queue<std::unique_ptr<Wave>> mWaves;
	sf::Time mTimeToNextWave = sf::seconds(5);
	sf::Time mElapsedTime = sf::Time::Zero;

	std::string mTitle;

	Stats mStats;

public:
	Level(sf::RenderWindow & window, const std::string &tmxMapPath, TextureHolder & textures);
	virtual void update(sf::Time dt) override;
	virtual void handleInput(const sf::Event & event) override;
	virtual void draw() override;
	void drawDebugInfo();
	void saveStatsToFile(const std::string &lvlName, const std::string gameOverMsg);

private:
	void placeTowerSlots();
	void buildScene();
	void updateSelectedTowerHudData();
	void handleCollisions();

	void directTowers();
	void startNextWave();

	void loadFromXml(const std::string & filename);

	virtual void loadAssets() override;
};


#include "Level.h"
#include "Path.h"
#include "Utility.h"
#include "Wave.h"
#include "Tower.h"
#include "TowerSlot.h"
#include "HUD.h"
#include "Projectile.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "tmxlite\detail\pugixml.hpp"
#include "Button.h"
#include "GameEvent.h"
#include "InvalidXmlException.h"



Level::Level(sf::RenderWindow & window, const std::string &xmlFilePath, TextureHolder & textures)
	: AppState(window, textures)
{
	loadAssets();
	loadFromXml(xmlFilePath);
	buildScene();
}

void Level::update(sf::Time dt)
{	
	mStats.time += dt;
	while (!mCommandQueue.empty())
	{
		mSceneGraph.onCommand(mCommandQueue.front(), dt);
		mPlayer.onCommand(mCommandQueue.front(), dt);
		mCommandQueue.pop();
	}
		
	directTowers();
	mSceneGraph.update(dt, mCommandQueue);

	handleCollisions();
	mSceneGraph.removeDestroyed();

	if (mSceneLayers[Layer::LandEnemies]->getChildren().empty())
	{
		mElapsedTime += dt;
		if (mElapsedTime > mTimeToNextWave)
		{
			mElapsedTime = sf::Time::Zero;
			startNextWave();
		}
	}
	
}

void Level::updateSelectedTowerHudData()
{
	Command displaySelectedTower;
	displaySelectedTower.category = ReceiverCategory::HUD;
	displaySelectedTower.action = derivedAction<HUD>([&mTextures = mTextures](HUD &hud, sf::Time)
	{
		hud.updateTowerDisplay(mTextures);
	});
	mCommandQueue.push(displaySelectedTower);
	Command updateRangePreview;
	updateRangePreview.category = ReceiverCategory::TowerSlot;
	updateRangePreview.action = derivedAction<TowerSlot>([](TowerSlot& slot, sf::Time)
	{
		slot.updateRangePreview();
	});
	mCommandQueue.push(updateRangePreview);
}


void Level::handleInput(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case (sf::Keyboard::Num1):
			mPlayer.setSelectedTowerType(TowerType::Regular);
			updateSelectedTowerHudData();
			break;
		case (sf::Keyboard::Num2):
			mPlayer.setSelectedTowerType(TowerType::Splash);
			updateSelectedTowerHudData();
			break;
		default:
			break;
		}		
	}
	else if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		Command buildTower;
		buildTower.category = ReceiverCategory::TowerSlot;
		buildTower.action = derivedAction<TowerSlot>([mSelectedTowerType = mPlayer.getSelectedTowerType()](TowerSlot& slot, sf::Time)
		{
			slot.buildTowerIfClicked();
		});
		mCommandQueue.push(buildTower);
		//////////////////////////////////////////////////////////////////////////
		Command toButtons;
		toButtons.category = ReceiverCategory::Button;
		toButtons.action = derivedAction<Button>([](Button& button, sf::Time)
		{
			button.onClick();
		});
		mCommandQueue.push(toButtons);
		//////////////////////////////////////////////////////////////////////////
	}
}


void Level::drawDebugInfo()
{

	std::stringstream ss;
	ss << mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)).x << ", "
		<< mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow)).y << std::endl;
	mouseCoordsText.setString(ss.str());
	mWindow.draw(mouseCoordsText);
}

void Level::saveStatsToFile(const std::string & lvlName, const std::string gameOverMsg)
{
	std::ofstream file(lvlName + "_results");
	
	file << lvlName << ": " << gameOverMsg << std::endl;
	file << "Enemies killed: " << mStats.enemiesKilled << std::endl;
	file << "Enemy hits: " << mStats.hits << std::endl;
	file << "Time passed: " << mStats.time.asSeconds() << " s" << std::endl;
}

void Level::draw()
{
	mWindow.draw(mSceneGraph);
}

void Level::loadAssets()
{
	mTextures.load(Textures::ID::EnemySoldier, "assets/textures/Soldiers/Green.png");
	mTextures.load(Textures::ID::EnemySupersoldier, "assets/textures/Soldiers/Grey.png");
	mTextures.load(Textures::ID::EnemyTank, "assets/textures/Soldiers/Tank.png");
	mTextures.load(Textures::ID::TowerRegular, "assets/textures/Turrets/TowerType1.png");
	mTextures.load(Textures::ID::TowerSplash, "assets/textures/Turrets/TowerSplash.png");
	mTextures.load(Textures::ID::ProjectileRegular, "assets/textures/Projectiles/ProjectileType1.png");
	mTextures.load(Textures::ID::ProjectileSplash, "assets/textures/Projectiles/ProjectileSplash.png");
	mTextures.load(Textures::ID::Slot, "assets/textures/Slots/Slot1.png");
	mTextures.load(Textures::ID::Button, "assets/textures/UI/Button.png");
	font.loadFromFile("assets/Fonts/OpenSans-Regular.ttf");
}

void Level::placeTowerSlots()
{
	std::vector<std::unique_ptr<TowerSlot>> towerSlots;
	auto &lays = mTmx.getLayers();
	for (auto &element : lays)
	{
		if (element->getName() == "TowerSlots")
		{
			const auto& objects = dynamic_cast<tmx::ObjectGroup*>(element.get())->getObjects();

			for (const auto& object : objects)
			{
				const auto &pos = object.getPosition();
				const auto &rect = object.getAABB();
				sf::RectangleShape slotRect(sf::Vector2f(rect.width, rect.height));
				slotRect.setPosition(pos.x, pos.y);
				std::unique_ptr<TowerSlot> slot(std::make_unique<TowerSlot>(slotRect, mTextures, mWindow, *mSceneLayers[Layer::Projectiles], mPlayer));
				mSceneLayers[Layer::Towers]->attachChild(std::move(slot));
			}
			return;
		}
	}
}


void Level::buildScene()
{

	for (std::size_t i = 0; i < Layer::LayerCount; ++i)
	{
		SceneNode::NodePtr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	std::unique_ptr<BackgroundMap> background(new BackgroundMap(mTmx));
	mSceneLayers[Layer::Background]->attachChild(std::move(background));

	placeTowerSlots();

	std::unique_ptr<HUD> hud(std::make_unique<HUD>(font, mPlayer));
	hud->updateTowerDisplay(mTextures);
	mSceneLayers[Layer::HUDLayer]->attachChild(std::move(hud));
}

void Level::handleCollisions()
{
	for (auto & wave : mSceneLayers[Layer::LandEnemies]->getChildren())
	{
		for (auto & enemy : wave->getChildren())
		{
			for (auto & projectile : mSceneLayers[Layer::Projectiles]->getChildren())
			{
				if (collision(*enemy, *projectile))
				{
					mStats.hits++;
					Projectile * castedProjectile = dynamic_cast<Projectile*> (projectile.get());
					Enemy * castedEnemy = dynamic_cast<Enemy*> (enemy.get());
					castedEnemy->takeDamage(castedProjectile->causeDamage());
					int droppedMoney = castedEnemy->dropMoney();
					if (droppedMoney)
						mStats.enemiesKilled++;
					mPlayer.addMoney(droppedMoney);
					projectile->markForRemoval();					
				}

			}
		}
	}
}

void Level::directTowers()
{
	for (auto & slot : mSceneLayers[Layer::Towers]->getChildren())
	{
		for (auto & tower : slot->getChildren())
		{
			Tower * castedTower = dynamic_cast<Tower*>  (tower.get());
			for (auto & wave : mSceneLayers[Layer::LandEnemies]->getChildren())
			{
				if (wave->getChildren().size() > 0)
				{
					float maxProgress = 0;
					castedTower->setTarget(nullptr);
					for (auto & enemy : wave->getChildren())
					{
						Enemy * castedEnemy = dynamic_cast<Enemy*> (enemy.get());
						if (castedTower->hasInRange(*castedEnemy) && castedEnemy->getProgress() > maxProgress)
						{
							maxProgress = castedEnemy->getProgress();
							castedTower->setTarget(castedEnemy);
						}
					}
				}
				else 
					castedTower->setTarget(nullptr);				
			}
		}
	}
}

void Level::startNextWave()
{	
	if (!mWaves.empty())
	{
		mSceneLayers[Layer::LandEnemies]->attachChild(std::move(mWaves.front()));
		mWaves.pop();
	}
	else if (mSceneLayers[Layer::LandEnemies]->getChildren().size() == 0)
	{
		GameEvent victory;
		victory.type = GameEvent::Type::GameWon;
		pushGameEvent(victory);
	}
}



void Level::loadFromXml(const std::string &filename)
{
	pugi::xml_document doc;
	auto result = doc.load_file(filename.c_str());

	if (result)
	{
		pugi::xml_node levelNode = doc.child("Level");
		auto tmxFilename = levelNode.attribute("tmxPath").value();
		mTmx.load(tmxFilename);

		Path path;
		path.loadFromTmx(mTmx);
		mPaths.push_back(path);

		for (pugi::xml_node &waveNode : levelNode.children())
		{
			const float interval = waveNode.attribute("interval").as_float();
			std::unique_ptr<Wave> wave(new Wave(interval));
			for (auto & child : waveNode.children())
			{
				const EnemyType::Type type = stringToEnum(child.attribute("type").value());
				const int count = child.attribute("count").as_int();
				const int pathId = child.attribute("pathId").as_int();
				wave->insertEnemies(count, type, mTextures, mPaths[pathId - 1]);
			}
			mWaves.push(std::move(wave));
		}
	}
	else
	{
		throw InvalidXmlException("Loading level aborted, invalid file: ");
	}
}



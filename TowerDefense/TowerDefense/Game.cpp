#include "Game.h"
#include "Enemy.h"
#include "Path.h"
#include "tmxlite\detail\pugixml.hpp"
#include "GameEvent.h"
#include "InvalidXmlException.h"

Game::Game() : mWindow(sf::VideoMode(mViewSize.x, mViewSize.y), "Tower Defense"),
mMainMenu(mWindow, mTextures),
mPauseScreen(mWindow, mTextures, nullptr),
mGameOverState(mWindow, mTextures, nullptr, "")
{
	mWindow.setView(mWindow.getDefaultView());
	loadLevelsList("assets/levels/levelList.xml");
	setMainMenuCallbacks();
	setPauseScreenCallbacks();
	setGameOverStateCallbacks();
	mBlackRect.setFillColor(sf::Color::Black);
	mBlackRect.setSize(sf::Vector2f(2000, 2000));
	mBlackRect.setPosition(mViewSize.x, 0);
	mCurrentState = &mMainMenu;

}


void Game::setMainMenuCallbacks()
{
	mMainMenu.mPrevLevelButton->setCallback([this]()
	{
		if (mSelectedLevelIndex > 0)
		{
			--mSelectedLevelIndex;
			mMainMenu.mSelectedLevelDisplay->setString(mLevels[mSelectedLevelIndex].first);
		}
	});
	mMainMenu.mNextLevelButton->setCallback([this]()
	{
		if (mSelectedLevelIndex < mLevels.size() - 1)
		{
			++mSelectedLevelIndex;
			mMainMenu.mSelectedLevelDisplay->setString(mLevels[mSelectedLevelIndex].first);
		}
	});
	mMainMenu.mLevelButton->setCallback([this](){ startSelectedLevel(); });
	mMainMenu.mExitButton->setCallback([this]() { mWindow.close(); });
}

void Game::setPauseScreenCallbacks()
{
	mPauseScreen.mContinueButton->setCallback([this]() { mCurrentState = mCurrentLevel.get(); });
	mPauseScreen.mReturnToMenuButton->setCallback([this]()
	{
		returnToMenu();
	});
	mPauseScreen.mExitButton->setCallback([this]() {mWindow.close(); });
}

void Game::setGameOverStateCallbacks()
{
	mGameOverState.mRestartButton->setCallback([this]() { startSelectedLevel(); });
	mGameOverState.mReturnToMenuButton->setCallback([this](){ returnToMenu(); });
	mGameOverState.mExitButton->setCallback([this]() {mWindow.close(); });
}


void Game::startSelectedLevel()
{
	try 
	{
		mCurrentLevel.reset(new Level(mWindow, mLevels[mSelectedLevelIndex].second, mTextures));
		mPauseScreen.setLevel(mCurrentLevel.get());
		mGameOverState.setLevel(mCurrentLevel.get());
		mCurrentState = mCurrentLevel.get();
	}
	catch (InvalidXmlException &e)
	{
		mCurrentLevel.reset();
		std::cout << e.what() << mLevels[mSelectedLevelIndex].second << std::endl;
	}
}

void Game::returnToMenu()
{
	mCurrentLevel.reset();
	mCurrentState = &mMainMenu;
}

void Game::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
		else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && mCurrentState == &mPauseScreen))
			mCurrentState = mCurrentLevel.get();
		else if ((event.type == sf::Event::LostFocus ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) && mCurrentState == mCurrentLevel.get())
			mCurrentState = &mPauseScreen;
		else if (event.type == sf::Event::Resized)
			onResize(event);
		else
			mCurrentState->handleInput(event);			
	}
	GameEvent gameEvent;
	while (pollGameEvent(gameEvent))
	{
		if (gameEvent.type == GameEvent::Type::GameLost)
		{
			std::string message = "Level failed!";
			mCurrentState = &mGameOverState;
			mGameOverState.setMessage(message);
			mCurrentLevel->saveStatsToFile(mLevels[mSelectedLevelIndex].first, message);
		}
		else if (gameEvent.type == GameEvent::Type::GameWon)
		{
			std::string message = "Level completed!";
			mCurrentState = &mGameOverState;
			mCurrentLevel->saveStatsToFile(mLevels[mSelectedLevelIndex].first, message);
			mGameOverState.setMessage(message);
		}
	}
}

void Game::onResize(const sf::Event &event)
{
	if (event.size.height < mViewSize.y || event.size.width < mViewSize.x)
	{
		mBlackRect.setPosition(mViewSize.x, 0);
		mWindow.setSize(mViewSize);
		mWindow.setView(sf::View(sf::FloatRect(0, 0, 0, 0)));
	}
	else
	{
		mBlackRect.setPosition(mViewSize.x, 0);
		auto offsetY = float(event.size.height - mViewSize.y) / 2.f;
		auto offsetX = float(event.size.width - mViewSize.x) / 2.f;
		sf::View view(sf::Vector2f((event.size.width) / 2.f - offsetX, (event.size.height) / 2.f - offsetY),
			sf::Vector2f(event.size.width, event.size.height));
		mWindow.setView(view);
	}
}

void Game::update(sf::Time dt)
{
	mCurrentState->update(dt);
}

void Game::render()
{
	mWindow.clear();

	mCurrentState->draw();
	mWindow.draw(mBlackRect);
	mWindow.display();
}

void Game::loadLevelsList(const std::string & filename)
{
	pugi::xml_document doc;

	if (!doc.load_file(filename.c_str()))
		throw std::exception();

	for (pugi::xml_node &levelNode : doc.children("Level"))
	{
		auto levelName = levelNode.attribute("name").value();
		auto levelFilePath = levelNode.attribute("fileName").value();
		mLevels.push_back(std::make_pair<std::string, std::string>(levelName, levelFilePath));
	}

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();	
	}
}


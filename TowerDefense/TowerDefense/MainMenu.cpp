#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow & window, TextureHolder & textures) : AppState(window, textures) 
{
	loadAssets();
	mBackground.setFillColor(sf::Color(0, 255, 0,50));
	mBackground.setSize(sf::Vector2f(window.getSize()));

	std::unique_ptr<TextNode> selectedLevelDisplay(std::make_unique<TextNode>(mFont, "Level 1"));
	selectedLevelDisplay->centerOrigin();
	selectedLevelDisplay->setPosition(480, 350);
	selectedLevelDisplay->setTextColor(sf::Color::White);

	mSelectedLevelDisplay = selectedLevelDisplay.get();
	mSceneGraph.attachChild(std::move(selectedLevelDisplay));

	setupButtons();

	std::unique_ptr<TextNode> title(std::make_unique<TextNode>(mFont, "Tower Defense"));
	title->setPosition(480, 200);
	title->setTextSize(50);
	title->centerOrigin();
	mSceneGraph.attachChild(std::move(title));
}

void MainMenu::setupButtons()
{
	std::unique_ptr<Button> prevLevelButton(std::make_unique<Button>(mWindow, mTextures, "", mFont, Textures::ID::ButtonLeftArrow));
	prevLevelButton->setPosition(400, 350);
	mPrevLevelButton = prevLevelButton.get();
	mSceneGraph.attachChild(std::move(prevLevelButton));

	std::unique_ptr<Button> nextLevelButton(std::make_unique<Button>(mWindow, mTextures, "", mFont, Textures::ID::ButtonRightArrow));
	nextLevelButton->setPosition(560, 350);
	mNextLevelButton = nextLevelButton.get();
	mSceneGraph.attachChild(std::move(nextLevelButton));

	std::unique_ptr<Button> levelButton(std::make_unique<Button>(mWindow, mTextures, "Select level", mFont, Textures::ID::Button));
	levelButton->setPosition(480, 400);
	mLevelButton = levelButton.get();
	mSceneGraph.attachChild(std::move(levelButton));

	std::unique_ptr<Button> exitButton(std::make_unique<Button>(mWindow, mTextures, "Exit game", mFont, Textures::ID::Button));
	exitButton->setPosition(480, 500);
	mExitButton = exitButton.get();
	mSceneGraph.attachChild(std::move(exitButton));
}

void MainMenu::handleInput(const sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
	{
		Command toButtons;
		toButtons.category = ReceiverCategory::Button;
		toButtons.action = derivedAction<Button>([](Button& button, sf::Time)
		{
			button.onClick();
		});
		mCommandQueue.push(toButtons);
	}
}

void MainMenu::draw()
{
	mWindow.draw(mBackground);
	mWindow.draw(mSceneGraph);
}

void MainMenu::update(sf::Time dt)
{
	while (!mCommandQueue.empty())
	{
		mSceneGraph.onCommand(mCommandQueue.front(), dt);
		mCommandQueue.pop();
	}
	mSceneGraph.update(dt, mCommandQueue);
}

void MainMenu::loadAssets()
{
	mTextures.load(Textures::ID::ButtonLeftArrow, "assets/textures/UI/arrowLeft.png");
	mTextures.load(Textures::ID::ButtonRightArrow, "assets/textures/UI/arrowRight.png");
	mTextures.load(Textures::ID::Button, "assets/textures/UI/Button.png");
	mFont.loadFromFile("assets/Fonts/OpenSans-Regular.ttf");
}


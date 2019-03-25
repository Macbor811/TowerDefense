#include "PauseScreen.h"
#include <iostream>


PauseScreen::PauseScreen(sf::RenderWindow & window, TextureHolder & textures, Level *level) : AppState(window, textures), mLevel(level)
{
	loadAssets();
	sf::Vector2f size(mWindow.getSize().x, mWindow.getSize().x);
	mDarkBackground.setSize(size);
	mDarkBackground.setFillColor(sf::Color(0, 0, 0, 100));

	std::unique_ptr<Button> continueButton(std::make_unique<Button>(mWindow, mTextures, "Resume", mFont, Textures::ID::Button));
	continueButton->setPosition(480, 400);
	mContinueButton = continueButton.get();
	mSceneGraph.attachChild(std::move(continueButton));


	std::unique_ptr<Button> returnToMenuButton(std::make_unique<Button>(mWindow, mTextures, "Return to menu", mFont, Textures::ID::Button));
	returnToMenuButton->setPosition(480, 480);
	mReturnToMenuButton = returnToMenuButton.get();
	mSceneGraph.attachChild(std::move(returnToMenuButton));

	std::unique_ptr<Button> exitButton(std::make_unique<Button>(mWindow, mTextures, "Exit game", mFont, Textures::ID::Button));
	exitButton->setPosition(480, 560);
	mExitButton = exitButton.get();
	mSceneGraph.attachChild(std::move(exitButton));

}

void PauseScreen::handleInput(const sf::Event &event)
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



void PauseScreen::draw()
{
	mLevel->draw();
	mWindow.draw(mDarkBackground);
	mWindow.draw(mSceneGraph);

}

void PauseScreen::update(sf::Time dt)
{
	while (!mCommandQueue.empty())
	{
		mSceneGraph.onCommand(mCommandQueue.front(), dt);
		mCommandQueue.pop();
	}
	mSceneGraph.update(dt, mCommandQueue);
	mSceneGraph.removeDestroyed();
}

void PauseScreen::loadAssets()
{
	mTextures.load(Textures::ID::Button, "assets/textures/UI/Button.png");
	mFont.loadFromFile("assets/Fonts/OpenSans-Regular.ttf");
}

void PauseScreen::setLevel(Level * level)
{
	mLevel = level;
}

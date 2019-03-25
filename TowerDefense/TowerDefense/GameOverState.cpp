#include "GameOverState.h"
#include "Game.h"




GameOverState::GameOverState(sf::RenderWindow & window, TextureHolder & textures, Level * level, const std::string &message) : 
	AppState(window, textures),
	mLevel(level)
{
	loadAssets();
	sf::Vector2f size(mWindow.getSize().x, mWindow.getSize().x);
	mDarkBackground.setSize(size);
	mDarkBackground.setFillColor(sf::Color(0, 0, 0, 100));

	std::unique_ptr<Button> restartButton(std::make_unique<Button>(mWindow, mTextures, "Restart level", mFont, Textures::ID::Button));
	restartButton->setPosition(480, 400);
	mRestartButton = restartButton.get();
	mSceneGraph.attachChild(std::move(restartButton));


	std::unique_ptr<Button> returnToMenuButton(std::make_unique<Button>(mWindow, mTextures, "Return to menu", mFont, Textures::ID::Button));
	returnToMenuButton->setPosition(480, 480);
	mReturnToMenuButton = returnToMenuButton.get();
	mSceneGraph.attachChild(std::move(returnToMenuButton));

	std::unique_ptr<Button> exitButton(std::make_unique<Button>(mWindow, mTextures, "Exit game", mFont, Textures::ID::Button));
	exitButton->setPosition(480, 560);
	mExitButton = exitButton.get();
	mSceneGraph.attachChild(std::move(exitButton));

	std::unique_ptr<TextNode> gameOverMessage(std::make_unique<TextNode>(mFont, message));
	gameOverMessage->centerOrigin();
	gameOverMessage->setPosition(480, 300);
	gameOverMessage->setTextColor(sf::Color::White);
	gameOverMessage->setTextSize(40);

	mMessage = gameOverMessage.get();
	mSceneGraph.attachChild(std::move(gameOverMessage));
}

void GameOverState::handleInput(const sf::Event & event)
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

void GameOverState::setMessage(const std::string &message)
{
	mMessage->setString(message);
	mMessage->centerOrigin();
}

void GameOverState::draw()
{
	mLevel->draw();
	mWindow.draw(mDarkBackground);
	mWindow.draw(mSceneGraph);
}

void GameOverState::update(sf::Time dt)
{
	while (!mCommandQueue.empty())
	{
		mSceneGraph.onCommand(mCommandQueue.front(), dt);
		mCommandQueue.pop();
	}
	mSceneGraph.update(dt, mCommandQueue);
	mSceneGraph.removeDestroyed();
}

void GameOverState::loadAssets()
{
	mTextures.load(Textures::ID::Button, "assets/textures/UI/Button.png");
	mFont.loadFromFile("assets/Fonts/OpenSans-Regular.ttf");
}

void GameOverState::setLevel(Level * level)
{
	mLevel = level;
}

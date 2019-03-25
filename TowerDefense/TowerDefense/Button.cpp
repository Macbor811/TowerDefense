#include "Button.h"



Button::Button(sf::RenderWindow &window, const TextureHolder& textures, const std::string &text, const sf::Font& font, Textures::ID textureId) :
	mWindow(window),
	mSprite(textures.get(textureId))
{

	sf::FloatRect bounds = mSprite.getGlobalBounds();
	mSprite.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	std::unique_ptr<TextNode> buttonText(std::make_unique<TextNode>(font, text));
	buttonText->setTextColor(sf::Color::Black);
	buttonText->centerOrigin();
	mText = buttonText.get();
	attachChild(std::move(buttonText));
}

void Button::onClick()
{
	const auto globalBounds = getLevelTransform().transformRect(mSprite.getGlobalBounds());
	if (globalBounds.contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))))
	{
		mCallback();
	}
}

void Button::setCallback(std::function<void()> callback)
{
	mCallback = std::move(callback);
}

void Button::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Button::getCategory() const
{
	return ReceiverCategory::Button;
}
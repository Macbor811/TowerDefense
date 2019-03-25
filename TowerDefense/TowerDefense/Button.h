#pragma once
#include "SceneNode.h"
#include "TextNode.h"
#include "TextureHolder.h"
#include <string>
#include <iostream>

class Button : public SceneNode
{
	std::function<void()> mCallback = []() { std::cout << "No function attached!" << std::endl; };
	sf::Sprite mSprite;
	sf::RenderWindow &mWindow;
	TextNode * mText;
	std::unique_ptr<sf::Font> mFont;
public:
	Button(sf::RenderWindow &mWindow, const TextureHolder& textures, const std::string &text, const sf::Font& font, Textures::ID textureId);
	void onClick();
	void setCallback(std::function<void()> callback);
	unsigned int getCategory() const;
private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

};

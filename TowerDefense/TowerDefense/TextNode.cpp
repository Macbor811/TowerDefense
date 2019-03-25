#include "TextNode.h"




TextNode::TextNode(const sf::Font& font, const std::string& text)
{
	mText.setFont(font);
	mText.setCharacterSize(20);
	setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states);
}

void TextNode::setString(const std::string& text)
{
	mText.setString(text);	
}

void TextNode::centerOrigin()
{
	sf::FloatRect bounds = mText.getLocalBounds();
	mText.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void TextNode::setTextSize(unsigned size)
{
	mText.setCharacterSize(size);
}

void TextNode::setTextColor(const sf::Color & color)
{
	mText.setFillColor(color);
}

void TextNode::setTextOutlineThickness(float thickness)
{
	mText.setOutlineThickness(thickness);
}


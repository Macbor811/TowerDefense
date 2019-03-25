#pragma once
#include "SceneNode.h"
class TextNode : public SceneNode
{
	sf::Text mText;

public:
	explicit TextNode(const sf::Font& font, const std::string& text);
	void setString(const std::string& text);
	void centerOrigin();
	void setTextSize(unsigned size);
	void setTextColor(const sf::Color &color);

	void setTextOutlineThickness(float thickness);


private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	
};


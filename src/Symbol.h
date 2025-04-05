#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Symbol
{
public:
	enum Type { TRIANGLE, STAR, CIRCLE, SQUARE };
	Symbol(Type type, sf::Vector2f pos, float size);
	Symbol();
	float getSize() const;
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);
	void draw(sf::RenderTarget& target);
	Type getType() const;
private:
	void createShape();
	void setColor();
	float m_Size;
	Type m_Type;
	sf::Vector2f m_Position;
	sf::ConvexShape m_Shape;
};


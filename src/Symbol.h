#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
using namespace sf;
using namespace std;

class Symbol
{
public:
	enum Type { TRIANGLE, STAR, CIRCLE, SQUARE };
	Symbol(Type type, Vector2f pos, float size);
	Symbol();
	float getSize() const;
	Vector2f getPosition() const;
	void setPosition(Vector2f pos);
	void draw(RenderTarget& target);
	Type getType() const;
private:
	void createShape();
	void setColor();
	float m_Size;
	Type m_Type;
	Vector2f m_Position;
	ConvexShape m_Shape;
};


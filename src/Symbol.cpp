#include "Symbol.h"

#include <iostream>
#define PI 3.1415926535897f


Symbol::Symbol(Type type, Vector2f pos, float size)
	:m_Type(type), m_Position(pos), m_Size(size)
{
	createShape();
}

Symbol::Symbol()
	: m_Type(TRIANGLE), m_Position(0, 0), m_Size(50.f)
{ 
	createShape();
}

void Symbol::createShape()
{
	switch (m_Type)
	{
		case TRIANGLE:
		{	
			m_Shape.setPointCount(3);
			m_Shape.setPoint(0, Vector2f(0.f, -m_Size/2));
			m_Shape.setPoint(1, Vector2f(-m_Size/2, m_Size/2));
			m_Shape.setPoint(2, Vector2f(m_Size/2, m_Size/2));
			m_Shape.setFillColor(Color::Magenta);
			break;
		}
		case STAR:
		{
			m_Shape.setPointCount(10);
			for (size_t i = 0; i < 10; ++i)
			{
				float angle = (float)(i * PI / 5);
				float radius = (i % 2 == 0) ? m_Size/2: m_Size/4;
				m_Shape.setPoint(i, Vector2f(radius * cos(angle - PI / 2), radius * sin(angle - PI / 2)));
			}
			m_Shape.setFillColor(Color::Yellow);
			break;
		}
		case CIRCLE:
		{
			m_Shape.setPointCount(60);
			for (size_t i = 0; i < 60; ++i)
			{
				float angle = (float)(i * 2 *  PI / 60);
				m_Shape.setPoint(i, Vector2f(m_Size/2* cos(angle), m_Size/2 * sin(angle)));
			}
			m_Shape.setFillColor(Color::Red);
			break;
		}
		case SQUARE:
		{
			m_Shape.setPointCount(4);
			m_Shape.setPoint(0, Vector2f(-m_Size/2, -m_Size/2));
			m_Shape.setPoint(1, Vector2f(m_Size/2, -m_Size/2));
			m_Shape.setPoint(2, Vector2f(m_Size/2, m_Size/2));
			m_Shape.setPoint(3, Vector2f(-m_Size/2, m_Size/2));
			m_Shape.setFillColor(Color::Green);
			break;
		}
	}
}

void Symbol::setPosition(Vector2f pos)
{
	m_Position = pos;
}

Vector2f Symbol::getPosition() const
{
	return m_Position;
}

float Symbol::getSize() const
{
	return m_Size;
}

Symbol::Type Symbol::getType() const
{
	return m_Type;
}

void Symbol::draw(RenderTarget& target)
{
	Vector2f curThickness = Vector2f(m_Shape.getScale().x - 2.f, m_Shape.getScale().y - 2.f);
	m_Shape.setOrigin(0.f , 0.f);
	m_Shape.setPosition(m_Position);
	target.draw(m_Shape);
}
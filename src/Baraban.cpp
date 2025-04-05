#include "Baraban.h"

#include <random>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

Baraban::Baraban(int numObjects, Vector2f size, Vector2f pos)
	:m_CountSymbols(numObjects), m_Size(size), m_Pos(pos), m_V(0.f),
	m_PosY(0.f), m_A(0.f), m_SymbolSize(0.f), m_State(States::Stop)
{
	generateAcceleration();
	generateSymbols();
	initShape();
}

void Baraban::initShape()
{
	m_Shape.setSize(m_Size);
	m_Shape.setOutlineThickness(thickness);
	m_Shape.setOutlineColor(sf::Color::White);
	m_Shape.setFillColor(sf::Color::Transparent);
	m_Shape.setPosition(m_Pos);
}

void Baraban::startSpin()
{
	m_State = States::Accelerating;
}

void Baraban::setDeceleratingStatus()
{
	m_State = States::Deccelerating;
}

float Baraban::calculateYPos(float numPos)
{
	return m_SymbolSize / 2 + spacing / 2 + thickness + (numPos * (m_SymbolSize + spacing));
}

float Baraban::calcSize() const
{
	float sizeShapeX = (m_Size.y - m_CountSymbols * spacing) / m_CountSymbols;
	float sizeShapeY = (m_Size.x - m_CountSymbols * spacing) / m_CountSymbols;
	return max(sizeShapeX, sizeShapeY);
}

void Baraban::generateAcceleration()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> accelerationDist(6.f, 14.f);

	m_A = accelerationDist(gen);
}

void Baraban::generateSymbols()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> shapeDist(0, 3);

	m_SymbolSize = calcSize();

	for (int i = 0; i < m_CountSymbols; ++i)
	{
		Symbol::Type type = static_cast<Symbol::Type>(shapeDist(gen));

		float xPos = m_Pos.x + m_Size.x / 2;
		float yPos = calculateYPos(static_cast<int>(i));
		Vector2f position(
			xPos
			, yPos
		);

		m_Symbols.emplace_back(type, position, m_SymbolSize);
	}
}

vector<Symbol> Baraban::getListSymbols() const
{
	vector<Symbol> actualSymbols;
	int roundPos = m_Symbols.size() - static_cast<int>(round(m_PosY));
	for (int i = roundPos; i < m_Symbols.size(); ++i)
	{
		actualSymbols.emplace_back(m_Symbols[i]);
	}
	for (int i = 0; i < roundPos; ++i)
	{
		actualSymbols.emplace_back(m_Symbols[i]);
	}
	return actualSymbols;
}

Vector2f Baraban::getPosition() const
{
	return m_Pos;
}

Vector2f Baraban::getSize() const
{
	return m_Size;
}

int Baraban::getCountElements() const
{
	return m_Symbols.size();
}

//Baraban::States Baraban::getState() const
//{
//	return m_State;
//}

bool Baraban::getStopSpinStatus() const
{
	return m_State == States::Stop;
}

void Baraban::accelerating(float diff)
{
	m_V += m_A * diff;
	if (m_V > maxSpeed) {
		m_V = maxSpeed;
		m_State = States::Deccelerating;
		return;
	}
	updatePosition(m_V * diff);
}

void Baraban::deccelerating(float diff)
{
	if (m_V < 0.001f)
	{
		m_V = 0.f;
		m_State = States::CorrectPos;
		return;
	}
	m_V -= m_A * diff * 3.f;
	updatePosition(m_V * diff);
}

void Baraban::correctPos(float diff)
{

	float posDiff = ceil(m_PosY) - m_PosY;
	if (fabs(posDiff) < 0.001f)
	{
		m_State = States::Stop;
		return;
	}
	constexpr float correctSpeed = 0.9f;
	float timeCorrect = correctSpeed * diff;
	float posCorrect = fabs(posDiff);
	float correct = min(posCorrect, timeCorrect);

	updatePosition((posDiff > 0) ? correct : -correct);
}

void Baraban::updatePosition(float diffPos)
{
	m_PosY += diffPos;
	if (m_PosY >= m_Symbols.size())
	{
		m_PosY -= m_Symbols.size();
	}
}

void Baraban::update(float diff)
{
	
	switch (m_State)
	{
		case States::Accelerating:
		{
			accelerating(diff);
			break;
		}

		case States::Deccelerating:
		{
			deccelerating(diff);
			break;
		}

		case States::CorrectPos:
		{
			correctPos(diff);
			break;
		}
		case States::Stop:
		{
			break;
		}
	}
}

void Baraban::draw(RenderTarget& target)
{
	for (size_t i = 0; i < m_Symbols.size(); ++i)
	{
		float numPos = i + m_PosY;
		if (numPos > m_Symbols.size())
		{
			numPos -= m_Symbols.size();
		}
		float yPos = calculateYPos(numPos);
		m_Symbols[i].setPosition(Vector2f(m_Symbols[i].getPosition().x, yPos));
		m_Symbols[i].draw(target);
		if (numPos > m_Symbols.size() - 1)
		{
			numPos -= m_Symbols.size();
			float yPos = calculateYPos(numPos);
			m_Symbols[i].setPosition(Vector2f(m_Symbols[i].getPosition().x, yPos));
			m_Symbols[i].draw(target);
		}
	}
	target.draw(m_Shape);
}


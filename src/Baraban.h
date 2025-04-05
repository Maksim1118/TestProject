#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Symbol.h"
#include "Combination.h"

constexpr float thickness = 5.f;
constexpr float spacing = 20.f;
constexpr float maxSpeed = 30.0f;

class Baraban
{
public:
	Baraban(int numShapes, sf::Vector2f size, sf::Vector2f pos);
	enum class States
	{
		Accelerating,
		Deccelerating,
		CorrectPos,
		Stop
	};

	void update(float diff);
	void draw(sf::RenderTarget& target);
	void startSpin();
	void setDeceleratingStatus();

	bool getStopSpinStatus() const;
	sf::Vector2f getSize() const;
	int getCountElements() const;
	sf::Vector2f getPosition() const;
	/*States getState() const;*/
	std::vector<Symbol> getListSymbols() const;
private:
	void generateSymbols();
	void generateAcceleration();
	float calculateYPos(float numPos);
	float calcSize() const;
	void initShape();

	void accelerating(float diff);
	void deccelerating(float diff);
	void correctPos(float diff);
	void updatePosition(float speed);

	std::vector<Symbol> m_Symbols;
	float m_V;
	float m_A;
	float m_PosY;

	float m_SymbolSize;
	int m_CountSymbols;
	States m_State;

	sf::RectangleShape m_Shape;
	sf::Vector2f m_Size;
	sf::Vector2f m_Pos;
};


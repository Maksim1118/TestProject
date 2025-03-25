#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Symbol.h"
#include "Combination.h"
using namespace sf;
using namespace std;

constexpr float thickness = 5.f;
constexpr float spacing = 20.f;
constexpr float maxSpeed = 30.0f;

class Baraban
{
public:
	Baraban(int numShapes, Vector2f size, Vector2f pos);
	enum class States
	{
		Accelerating,
		Deccelerating,
		CorrectPos,
		Stop
	};

	void update(float diff);
	void draw(RenderTarget& target);
	void startSpin();
	void setDeceleratingStatus();

	bool getStopSpinStatus() const;
	Vector2f getSize() const;
	int getCountElements() const;
	Vector2f getPosition() const;
	/*States getState() const;*/
	vector<Symbol> getListSymbols() const; 
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

	vector<Symbol> m_Symbols;
	float m_V;
	float m_A;
	float m_PosY;

	float m_SymbolSize;
	int m_CountSymbols;
	States m_State;

	RectangleShape m_Shape;
	Vector2f m_Size;
	Vector2f m_Pos;
};


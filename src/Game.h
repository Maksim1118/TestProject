#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <utility>

#include "BarabanManager.h"
#include "Button.h"
#include "StateMachine.h"
using namespace std;
using namespace sf;

constexpr size_t windowWidth = 1920;
constexpr size_t windowHeight = 1080;

constexpr size_t barabanWidth = 300.f;
constexpr size_t barabanHeight = 800.f;

constexpr unsigned int numBarabans = 3;
constexpr unsigned int numSymbols = 4;

class Game
{
public:
	Game();
	void run();
	static vector<pair<Combination, unsigned int>> m_WinCombinations;
private:
	void events();
	void draw();
	void createWinCombinations();
	bool match(const Combination& combination);

    BarabanManager m_BarabanManager;
	Button m_ButStart;
	Button m_ButStop;
    StateMachine m_StateMachine;

	Font m_Font;
	Text m_BalanceText;
	Text m_WinText;
	RenderWindow window;
    Clock m_Clock;
};


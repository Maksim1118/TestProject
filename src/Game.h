#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <utility>

#include "BarabanManager.h"
#include "Button.h"
#include "StateMachine.h"

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
	static std::vector<std::pair<Combination, unsigned int>> m_WinCombinations;
private:
	void events();
	void draw();
	void createWinCombinations();
	bool match(const Combination& combination);

    BarabanManager m_BarabanManager;
	Button m_ButStart;
	Button m_ButStop;
    StateMachine m_StateMachine;

	sf::Font m_Font;
	sf::Text m_BalanceText;
	sf::Text m_WinText;
	sf::RenderWindow window;
    sf::Clock m_Clock;
};


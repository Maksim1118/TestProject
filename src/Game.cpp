#include "Game.h"
#include <stdexcept>

using namespace sf;
using namespace std;

Game::Game()
	:window(VideoMode(windowWidth, windowHeight), "SlotGame", Style::Titlebar | Style::Close), m_BarabanManager(numBarabans, numSymbols, Vector2f(barabanWidth, barabanHeight))
    , m_StateMachine(m_BarabanManager), m_ButStart(L"start"),m_ButStop(L"stop"), m_Clock()
{
    if (!m_Font.loadFromFile("Fonts/PublicPixel.ttf"))
    {
        throw std::runtime_error("Fail load fonts");
    }
	window.setFramerateLimit(240);
    createWinCombinations();
    Vector2f sizeBarabans = m_BarabanManager.getSize();

    m_BalanceText.setPosition(Vector2f(100.f, 50.f));
    m_BalanceText.setCharacterSize(24);
    m_BalanceText.setFillColor(Color::White);
    m_BalanceText.setFont(m_Font);

    m_WinText.setPosition(Vector2f(100.f + sizeBarabans.x/2, 50.f));
    m_WinText.setCharacterSize(24);
    m_WinText.setFillColor(Color::White);
    m_WinText.setFont(m_Font);

    m_ButStart.setPosition(Vector2f(130 + sizeBarabans.x, 100.f));
    m_ButStart.setSize(Vector2f(200.f, 200.f));

    m_ButStop.setPosition(Vector2f(130 + sizeBarabans.x, sizeBarabans.y - 100.f));
    m_ButStop.setSize(Vector2f(200.f, 200.f));
}

void Game::run()
{
    createWinCombinations();
    while (window.isOpen()) {

        float deltaTime = m_Clock.restart().asSeconds();
        events();
        m_StateMachine.update(deltaTime);
        Stats stats = m_BarabanManager.getStats();
        m_BalanceText.setString("Balance: " + to_string(stats.m_Balance));
        m_WinText.setString("Win: " + to_string(stats.m_Win));
        draw();
    }
}

void Game::createWinCombinations()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> winDist(3, 30);

    for (int i = 0; i < 10; ++i)
    {
        Combination newCombination;
        do
        {
            newCombination.generate();
        } while (match(newCombination));

        Stats stats = m_BarabanManager.getStats();
        unsigned int win = winDist(gen) * stats.m_Bet;
        m_WinCombinations.emplace_back(move(newCombination), win);
    }
}

bool Game::match(const Combination& combination)
{
    for (int i = 0; i < m_WinCombinations.size(); ++i)
    {
        if (m_WinCombinations[i].first == combination)
            return true;
    }
    return false;
}

void Game::events()
{
    Event event;
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (m_ButStart.isPos(mousePos.x, mousePos.y))
            {
                m_StateMachine.start();
            }
            if (m_ButStop.isPos(mousePos.x, mousePos.y))
            {
                m_StateMachine.stop();
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::draw()
{
    window.clear(Color(0.f, 0.f, 70.f));
    m_BarabanManager.draw(window);
    m_ButStart.draw(window);
    m_ButStop.draw(window);
    window.draw(m_BalanceText);
    window.draw(m_WinText);
    window.display();
}

vector<pair<Combination, unsigned int>>& getWinCombinations()
{
    return Game::m_WinCombinations;
}

vector<pair<Combination, unsigned int>> Game::m_WinCombinations;
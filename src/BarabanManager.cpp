#include "BarabanManager.h"

#include <random>
#include <iostream>
using namespace sf;
using namespace std;

vector<pair<Combination, unsigned int>>& getWinCombinations();

BarabanManager::BarabanManager(int countBarabans, int countObjects, Vector2f size)
    :m_State(States::Wait), m_StateShowWin(StatesShowWin::check), m_Delay(2.f), 
    m_CurrentCombination(0), m_isDrawLine(false)
{
    fillListBarabans(countBarabans, countObjects, size);
    m_Mask.create(size.x * countBarabans + ((countBarabans + 1) * thickness), size.y + thickness*2);
}

void BarabanManager::setState(States state)
{
    m_State = state;
}

void BarabanManager::fillListBarabans(int countBarabans, int countObjects, Vector2f size)
{
    float offsetX = thickness;
    for (int i = 0; i < countBarabans; ++i)
    {
        m_Barabans.emplace_back(countObjects, size, Vector2f(offsetX, thickness));
        offsetX += m_Barabans[i].getSize().x + thickness;
    }
}

Vector2f BarabanManager::getSize() const
{
    return (Vector2f)m_Mask.getSize();
}

BarabanManager::States BarabanManager::getState() const
{
    return m_State;
}

void BarabanManager::startSpin()
{
    for (auto& baraban : m_Barabans)
    {
        baraban.startSpin();
    }
    m_State = States::Spinning;
}

void BarabanManager::setDecelerating()
{
    for (auto& baraban : m_Barabans)
    {
        baraban.setDeceleratingStatus();
    }
}

bool BarabanManager::stopSpinStatus()
{
    for (auto& baraban : m_Barabans)
    {
        if (!baraban.getStopSpinStatus())
            return false;
    }
    return true;
}

void BarabanManager::addWin(unsigned int amount)
{
    cout << amount << endl;
    m_Stats.m_Balance += amount;
    m_Stats.m_Win += amount;
}

void BarabanManager::collectingCombination(int index)
{
    int countRows = m_Barabans.size();
    Combination combination;
    vector<Vector2f> positions;
    for (int j = 0; j < countRows; ++j)
    {
        vector<Symbol> symbols = m_Barabans[j].getListSymbols();

        if (index < symbols.size())
        {
            combination.addCoombinationSymbol(symbols[index].getType());
            positions.emplace_back(symbols[index].getPosition());
        }
    }
    m_Combinations.emplace_back(combination, positions);
}

void BarabanManager::drawWiningLines(int index)
{
    vector<Vector2f> points = m_Combinations[index].second;

    for (size_t i = 0; i < points.size() - 1; ++i)
    {
        Vector2f start = points[i];
        Vector2f end = points[i + 1];
        Vector2f direction = end - start;

        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        RectangleShape line(Vector2f(length, 10.f));
        line.setOrigin(0, 5.f);
        line.setPosition(start);
        line.setFillColor(Color(120, 120, 120));
        line.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159);

        m_Lines.push_back(line);
    }
}

bool BarabanManager::checkWin(int index)
{
    vector<pair<Combination, unsigned int>>& winCombinations = getWinCombinations();
    for(int j = 0; j < winCombinations.size(); ++j)
    {
        if (m_Combinations[index].first == winCombinations[j].first)
        {
            addWin(winCombinations[j].second);
            return true;
        }
    }
    return false;
}

void BarabanManager::showWinDelay(float diff)
{
    m_Delay -= diff;
    if (m_Delay <= 0)
    {
        m_Delay = 3.f;
        m_StateShowWin = StatesShowWin::increasingIndex;
    }
}

Stats BarabanManager::getStats() const
{
    return m_Stats;
}

void BarabanManager::draw(RenderTarget& target)
{
    m_Mask.clear(Color::Transparent);

    for (auto& baraban : m_Barabans) {
        baraban.draw(m_Mask);
    }
    for (const auto& line : m_Lines) {
        m_Mask.draw(line);
    }
    m_isDrawLine = true;
    m_Mask.display();
    Sprite sprite(m_Mask.getTexture());

    sprite.setPosition(100.f, 100.f);

    target.draw(sprite);
}

void BarabanManager::update(float diff)
{
    switch (m_State)
    {
        case States::Start:
        {
            startSpin();
            m_Stats.m_Balance -= m_Stats.m_Bet;
            break;
        }
        case States::Spinning:
        {
            break;
        }
        case States::ShowWin:
        {
            switch (m_StateShowWin)
            {
                case StatesShowWin::check:
                {
                    collectingCombination(m_CurrentCombination);
                    if (checkWin(m_CurrentCombination))
                    {
                        m_StateShowWin = StatesShowWin::show;
                    }
                    else
                    {
                        m_StateShowWin = StatesShowWin::increasingIndex;
                    }
                    break;
                }
                case StatesShowWin::show:
                {
                    drawWiningLines(m_CurrentCombination);
                    m_StateShowWin = StatesShowWin::delay;
                    break;
                }
                case StatesShowWin::delay:
                {
                    showWinDelay(diff);
                    break;
                }
                case StatesShowWin::increasingIndex:
                {
                    m_CurrentCombination++;

                    if (m_isDrawLine)
                    {
                        if (m_CurrentCombination == m_Barabans[0].getCountElements())
                        {
                            m_CurrentCombination = 0;
                            m_State = States::Wait;
                            m_StateShowWin = StatesShowWin::check;
                            m_isDrawLine = false;
                        }
                        else
                        {
                            m_StateShowWin = StatesShowWin::check;
                            m_isDrawLine = false;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case States::Wait:
        {
            m_Lines.clear();
            m_Stats.m_Win = 0;
            m_Combinations.clear();
            break;
        }
    }

    for (int i = 0; i < m_Barabans.size(); ++i)
    {
        m_Barabans[i].update(diff);
    }
}

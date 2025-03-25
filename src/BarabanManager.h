#pragma once
#include "Baraban.h"
#include "Combination.h"

#include <future>
#include <thread>
#include <chrono>

struct Stats
{
    int m_Win;
    int m_Balance;
    int m_Bet;
    Stats() : m_Win(0), m_Balance(800), m_Bet(10) {}
};

class BarabanManager {
public:
    BarabanManager(int countBarabans, int countObjects, Vector2f size);
    enum class States
    {
        Wait,
        Start,
        Spinning,
        ShowWin
    };

    enum class StatesShowWin
    {
        check,
        delay,
        show,
        increasingIndex

    };
    
    void setState(States state);
    void setDecelerating();
    void startSpin();

    Vector2f getSize() const;
    Stats getStats() const;
    States getState() const;

    bool stopSpinStatus();
    void draw(RenderTarget& target);
    void update(float diff);

private:
    void fillListBarabans(int countBarabans, int countObjects, Vector2f size);
    void collectingCombination(int index);
    bool checkWin(int index);
    void showWinDelay(float diff);
    void addWin(unsigned int amount);
    void drawWiningLines(int index);

    float m_Delay;
    int m_CurrentCombination;
    bool m_isDrawLine;

    Stats m_Stats;
    States m_State;
    StatesShowWin m_StateShowWin;
    vector<Baraban> m_Barabans;
    vector<pair<Combination,vector<Vector2f>>> m_Combinations;
    RenderTexture m_Mask;
    vector<RectangleShape> m_Lines;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

constexpr float sizeX = 200.f;
constexpr float sizeY = 50.f;

class Button
{
public:
    Button(const wstring text);
    bool isPos(const float& x, const float& y);
    void setPosition(Vector2f pos);
    void setSize(Vector2f size);
    void draw(RenderWindow& window);
private:
    Text _title;
    RectangleShape m_Button;
    Font font;
    void createTitle(const wstring& text);
};




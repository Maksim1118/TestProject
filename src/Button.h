#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr float sizeX = 200.f;
constexpr float sizeY = 50.f;

class Button
{
public:
    Button(const std::wstring text);
    bool isPos(const float& x, const float& y);
    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void draw(sf::RenderWindow& window);
private:
    sf::Text _title;
    sf::RectangleShape m_Button;
    sf::Font font;
    void createTitle(const std::wstring& text);
};




#include "Button.h"

#include <stdexcept>

Button::Button(const wstring text)
{

    m_Button.setSize(Vector2f(100.f, 100.f));
    m_Button.setFillColor(Color::White);
    m_Button.setPosition(0.f, 0.f);

    createTitle(text);
}

void Button::setPosition(Vector2f pos)
{
    m_Button.setPosition(pos);
}

void Button::setSize(Vector2f size)
{
    m_Button.setSize(size);
}

bool Button::isPos(const float& x, const float& y)
{
    Vector2f pos = m_Button.getPosition();
    Vector2f size = m_Button.getSize();
    if (x < pos.x)
    {
        return false;
    }
    if (x > pos.x + size.x)
    {
        return false;
    }
    if (y < pos.y)
    {
        return false;
    }
    if (y > pos.y + size.y)
    {
        return false;
    }
    return true;
}
void Button::draw(RenderWindow& window)
{
    window.draw(m_Button);
    _title.setPosition(
        m_Button.getPosition().x + m_Button.getSize().x/2 - (_title.getGlobalBounds().width) / 2,
        m_Button.getPosition().y + m_Button.getSize().y/2 - (_title.getGlobalBounds().height) / 2
    );
    window.draw(_title);
}
void Button::createTitle(const wstring& text)
{
   
    if (!font.loadFromFile("Fonts/PublicPixel.ttf"))
    {
        throw std::runtime_error("Fail load fonts");
    }
       
    _title.setFont(font);
    _title.setString(text);
    _title.setCharacterSize(24);
    _title.setFillColor(Color::Cyan);
    _title.setStyle(Text::Bold);
}

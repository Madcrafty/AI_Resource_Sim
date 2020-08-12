#include "Button.h"
Button::Button(const std::string& text, Rectangle rect)
{
    m_text = text;
    m_rect = rect;
}
Button::Button(const std::string& text, Texture2D* h_false, Texture2D* h_true, Rectangle rect)
{
    m_text = text;
    m_default = h_false;
    m_hover = h_true;
    m_rect = rect;
}
Button::~Button()
{
}
void Button::Update()
{
    m_mouseOver = IsPointInRect(GetMousePosition(), m_rect);
    if (m_mouseOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // call our onClick method
        m_onClick();
    }
}
void Button::Draw()
{
    Color blank = Color{ 0,0,0,0 };
    auto color = m_mouseOver ? blank : blank;
    DrawRectangle(m_rect.x, m_rect.y, m_rect.width, m_rect.height, blank);
    auto& tex = m_mouseOver ? m_hover : m_default;
    DrawTexture(*tex, m_rect.x, m_rect.y, WHITE);
    DrawText(m_text.c_str(), m_rect.x, m_rect.y, 24, BLACK);
}
bool Button::IsPointInRect(Vector2 point, Rectangle rect)
{
    return point.x > rect.x && point.y > rect.y && point.x < rect.x + rect.width && point.y < rect.y + rect.height;
}
void Button::OnClick(std::function<void()> aaronsFunction)
{
    m_onClick = aaronsFunction;
}
void Button::SetText(const std::string& text)
{
    m_text = text;
}
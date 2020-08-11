#pragma once
#include <string>
#include <functional>
#include "raylib.h"
class Button
{
public:
    Button(const std::string& text, Rectangle rect);
    Button(const std::string& text, Texture2D* h_false, Texture2D* h_true, Rectangle rect);
    ~Button();
    void OnClick(std::function<void()> aaronsFunction);
    void Update();
    void Draw();
    void SetText(const std::string& text);
protected:
private:
    bool IsPointInRect(Vector2 point, Rectangle rect);
    std::string m_text;
    Texture2D* m_default;
    Texture2D* m_hover;
    Rectangle m_rect;
    bool m_mouseOver = false;
    std::function<void()> m_onClick;
};
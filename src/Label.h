#pragma once

#include <visage/app.h>
#include "embedded/example_fonts.h"
#include "embedded/fonts.h"

class Label : public visage::Frame
{
  public:
    Label() = default;
    visage::String text_;
    bool outline{true};
    std::vector<visage::String> tokens_;
    visage::Font fontEn{25, visage::fonts::Lato_Regular_ttf};
    visage::Color color_{visage::Color(0xff000000)};
    bool centered{true};
    void setColor(const visage::Color &color)
    {
        color_ = color;
        redraw();
    }
    void setText(const visage::String &text)
    {
        text_ = text;
        redraw();
    }
    void setText2(const char text[])
    {
        text_ = visage::String(text);
        redraw();
    }
    void setFont(const visage::Font &font)
    {
        fontEn = font.withDpiScale(dpiScale());
        redraw();
    }
    visage::Point indexToPosition(int index) const
    {
        if (index < 0 || index >= text_.length())
            return {0.0f, 0.0f};

        float x = fontEn.stringWidth(text_.c_str(), index);
        float y = fontEn.lineHeight();
        return {x, y};
    }

    void draw(visage::Canvas &canvas) override
    {
        canvas.setColor(0xff000000);
        if (outline)
        {
            canvas.rectangleBorder(0, 0, width(), height(), 1.0f);
        }
        if (text_.isEmpty())
        {
            return;
        }
        canvas.setColor(color_);
        if (centered)
            canvas.text(text_, fontEn, visage::Font::Justification::kCenter, 0, 0, width(),
                        height());
        else
            canvas.text(text_, fontEn, visage::Font::Justification::kTop, 0, 0, width(), height());
    }
};
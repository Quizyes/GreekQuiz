#pragma once

#include <string>
#include <iostream>
#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"
#include "embedded/fonts.h"
#include <visage_widgets/button.h>
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include <emscripten.h>
#include "DbManager.h"
#include "Label.h"
#include "QuizItem.h"
#include "Betacode.h"
#define MAX_ROWS 8

namespace gwr::gkqz
{

class App : public visage::ApplicationWindow
{
  public:
    App();
    ~App();
    void newQuiz();
    void newQuiz(int lesson);
    void getAlts();
    void markQuiz();
    void clearColors();
    bool userInputIsShown{true};
    bool quizIsMarked{false};
    static const ::visage::theme::ColorId WrongBkgd;
    static const ::visage::theme::ColorId RightBkgd;

    DbManager dbm;
    visage::Font font{50, visage::fonts::Lato_Regular_ttf};
    void draw(visage::Canvas &canvas) override;
    std::vector<std::string> splitForms(std::string entry);
    visage::UiButton newBtn{"New"}, markBtn{"Mark"}, helpBtn{"?"};
    Label lessonLabel, header, body; // , headword;
    visage::TextEditor lesson;
    std::array<QuizItem *, MAX_ROWS> cs;
};

} // namespace gwr::gkqz
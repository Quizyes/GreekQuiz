#pragma once

#include <string>
#include <iostream>
#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"
#include <visage_widgets/button.h>
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include "DbManager.h"
#include "Label.h"
#include "QuizItem.h"
#include "Betacode.h"

namespace gwr::gkqz
{

class App : public visage::ApplicationWindow
{
  public:
    App();
    void newQuiz();
    void newQuiz(int lesson);
    void markQuiz();
    void getAlts();
    void clearColors();
    void red(Label *l);
    void red(visage::TextEditor *e);
    void grn(Label *l);
    void grn(visage::TextEditor *e);
    void blk(Label *l);
    void blk(visage::TextEditor *e);
    void printDbEntry(dbEntry entry);
    bool userInputIsShown{true};
    bool quizIsMarked{false};
    static const ::visage::theme::ColorId WrongBkgd;
    static const ::visage::theme::ColorId RightBkgd;
    // remake in conj
    // bool matches(std::string &userAnswer, std::string &dbAnswer);

    // std::string replaceAccentedCharacters(std::string &input);
    // std::string replaceUnaccentedCharacters(std::string &input);
    SQLite::Statement getRightStatment(std::string &inverb);
    DbManager dbm;
    visage::Font font{20, resources::fonts::Lato_Regular_ttf};
    void draw(visage::Canvas &canvas) override;
    std::vector<std::string> splitForms(std::string entry);
    visage::UiButton newBtn{"New"}, markBtn{"Mark"};
    Label header, body; // , headword;
    visage::TextEditor lesson;
    QuizItem c1, c2, c3, c4, c5;
    std::array<QuizItem *, 5> cs;
    // Betacode b;
};

} // namespace gwr::gkqz
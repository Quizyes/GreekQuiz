////////////////////////////////////////////////////////////////////////// 
//                                                                      // 
// Greek Quiz - a suite of apps for practicing Ancient Greek.           // 
//                                                                      // 
// Copyright 2025, Greg Recco                                           // 
//                                                                      // 
// Greek Quiz is released under the GNU General Public Licence v3       // 
// or later (GPL-3.0-or-later). The license is found in the 'LICENSE'   // 
// file in the root of this repository, or at                           // 
// https://www.gnu.org/licenses/gpl-3.0.en.html                         // 
//                                                                      // 
// The source code repository for Greek Quiz is available at            // 
// https://github.com/Quizyes/GreekQuiz                                 // 
//                                                                      // 
////////////////////////////////////////////////////////////////////////// 

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
#include "QuizRevItem.h"
#include "Betacode.h"
#define MAX_ROWS 8

namespace gwr::gkqz
{

class App : public visage::ApplicationWindow
{
  public:
    App();
    ~App();
    void draw(visage::Canvas &canvas) override;
    void newQuiz();
    void newQuiz(int lesson);
    void getAlts();
    void markQuiz();
    void clearColors();
    void switchQs();
    bool userInputIsShown{true}, quizIsMarked{false}, isReverse{false};
    DbManager dbm;
    visage::Font font{50, visage::fonts::Lato_Regular_ttf};
    visage::UiButton newBtn{"New"}, markBtn{"Mark"}, helpBtn{"?"}, reverseBtn{"Reverse"};
    Label lessonLabel, header, body;
    visage::TextEditor lesson;
    std::array<QuizItem *, MAX_ROWS> qis;
    std::array<gwr::gkrv::QuizRevItem *, MAX_ROWS> qrs;
};

} // namespace gwr::gkqz
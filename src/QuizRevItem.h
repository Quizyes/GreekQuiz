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

#include <visage_app/application_window.h>
#include "embedded/example_fonts.h"
#include "Label.h"
#include "Betacode.h"
#include "Utils.h"
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include <visage_graphics/theme.h>
#include <set>

namespace gwr::gkrv
{

class QuizRevItem : public visage::Frame
{
  public:
    std::string name_{""};
    visage::Font fontEn{20, visage::fonts::Lato_Regular_ttf};
    visage::Font fontGk{20, resources::fonts::GFSDidot_Regular_ttf};
    QuizRevItem();
    void draw(visage::Canvas &canvas);
    void clearAll();
    void check();       // is head correct, is parse?
    void readEntries(); // load input into fields
    void color();       // color entries by correctness
    void show();        // show first correct answer
    void mark();        // wrap it all up into one
    void red(visage::TextEditor *e);
    void grn(visage::TextEditor *e);
    void blk(visage::TextEditor *e);
    bool inflectedIsCorrect{false};

    visage::Frame prompt, headword, parse;
    Label inflectedDb, headwordDb, parseDb;
    visage::TextEditor inflectedEditor; // user entry
    dbEntry userForm, dbForm;
};

} // namespace gwr::gkrv
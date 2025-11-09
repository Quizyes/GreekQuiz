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

#include "QuizItem.h"
#include <iostream>
#define QLOG(msg) std::cerr << "DEBUG: " << msg << std::endl;

using namespace visage::dimension;
using bc = Betacode;

namespace gwr::gkqz
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

QuizItem::QuizItem()
{
    layout().setFlex(true);
    layout().setFlexRows(false);
    addChild(&prompt, true);
    addChild(&headword, true);
    addChild(&parse, true);
    // layout().setPadding(2.f);

    headword.layout().setFlexRows(true);
    headword.layout().setPadding(2.f);
    parse.setFlexLayout(true);
    parse.layout().setFlex(true);
    parse.layout().setFlexRows(true);
    parse.layout().setPadding(2.f);
    parse.layout().setDimensions(50_vw, 100_vh);
    prompt.layout().setPadding(2.f);

    for (auto &fr : {&prompt, &headword})
    {
        fr->setFlexLayout(true);
        fr->layout().setDimensions(25_vw, 100_vh);
    }

    headword.addChild(&headwordUser, true);
    headword.addChild(&headwordDb, true);

    parse.addChild(&parseUser, true);
    parse.addChild(&parseDb, true);

    prompt.addChild(&promptDb, true);

    promptDb.setFont(fontGk.withSize(30.f));
    promptDb.layout().setDimensions(100_vw, 100_vh);
    promptDb.layout().setMargin(1_vh);
    promptDb.just = visage::Font::Justification::kCenter;

    headwordDb.setFont(fontGk.withSize(30.f));
    headwordDb.layout().setDimensions(100_vw, 100_vh);
    headwordDb.layout().setMargin(1_vh);

    for (auto &fr : {&headwordUser, &parseUser})
    {
        fr->setFont(fontGk.withSize(25.f));
        fr->layout().setDimensions(100_vw, 49_vh);
        fr->setTextFieldEntry();
    }
    headwordUser.setDefaultText("headword...");
    parseUser.setDefaultText("parse...");

    headwordUser.onTextChange() += [&]() {
        // mirror betacode with Greek
        headwordDb.setText(bc::beta2greek(headwordUser.text().toUtf8()));
    };

    headwordDb.layout().setDimensions(100_vw, 50_vh);
    parseDb.setFont(fontEn.withSize(30.f));
    parseDb.layout().setDimensions(100_vw, 50_vh);
    parseDb.layout().setMargin(1_vh);

    promptDb.outline = true;
    headwordDb.outline = true;
    parseDb.outline = true;
    userForm.id = 0;
    userForm.lesson = 0;
    userForm.head = "0";
    userForm.inflected = "0";
    userForm.parse = "0";
    // readEntries();
}

void QuizItem::draw(visage::Canvas &canvas) { canvas.setColor(0xff000000); }

void QuizItem::check()
{
    int idx{0};
    headIsCorrect = false;
    parseIsCorrect = false;
    for (auto &dbForm : dbForms)
    {
        bool headC{false}, parseC{false};
        if (userForm.head == dbForm.head)
        {
            headC = true;
            headIsCorrect = true;
        }
        if (compareParses(userForm.parse, dbForm.parse))
        {
            parseC = true;
            parseIsCorrect = true;
        }
        if (parseC && headC)
        {
            idxOfCorrectParse = idx;
            headIsCorrect = true;
            parseIsCorrect = true;
            return;
        }
        ++idx;
    }
}

void QuizItem::show()
{
    int idx{0};
    if (parseIsCorrect)
        idx = idxOfCorrectParse;
    auto &str = dbForms[idx].head;
    headwordDb.setText(bc::beta2greek(str));
    headwordUser.setText(bc::beta2greek(userForm.head));
    parseDb.setText(dbForms[idx].parse);
    redraw();
}

void QuizItem::mark()
{
    readEntries();
    check();
    color();
    show();
    redraw();
}

void QuizItem::red(visage::TextEditor *e)
{
    e->setBackgroundColorId(WRONG);
    e->redraw();
}

void QuizItem::grn(visage::TextEditor *e)
{
    e->setBackgroundColorId(RIGHT);
    e->redraw();
}

void QuizItem::blk(visage::TextEditor *e)
{
    e->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    e->redraw();
}

void QuizItem::readEntries()
{
    userForm.head = headwordUser.text().toUtf8();
    userForm.parse = parseUser.text().toUtf8();
}

void QuizItem::color()
{
    if (headIsCorrect)
        grn(&headwordUser);
    else
        red(&headwordUser);
    if (parseIsCorrect)
        grn(&parseUser);
    else
        red(&parseUser);
    redraw();
}

void QuizItem::clearAll()
{
    headwordUser.clear();
    parseUser.clear();
    headwordDb.setText("");
    parseDb.setText("");
    headwordUser.setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    parseUser.setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    headIsCorrect = false;
    parseIsCorrect = false;
    redraw();
    // set colors
}

bool QuizItem::compareParses(std::string &userParse, std::string &dbParse)
{
    int matches{0};
    auto userParts = split(userParse, ' ');
    auto dbParts = split(dbParse, ' ');
    for (auto &dbPart : dbParts)
    {
        if (userParts.contains(dbPart))
            ++matches;
    }
    auto m = (matches == dbParts.size());
    return m;
}

std::set<std::string> QuizItem::split(std::string &str, char delimiter)
{
    std::set<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.insert(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    tokens.insert(str.substr(start));
    return tokens;
}

} // namespace gwr::gkqz
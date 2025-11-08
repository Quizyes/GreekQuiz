#pragma once

#include <visage_app/application_window.h>
#include "embedded/example_fonts.h"
#include "Label.h"
#include "Betacode.h"
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include <visage_graphics/theme.h>
#include <set>

namespace gwr::gkqz
{

typedef struct dbEntry
{
    int id{0}, lesson{0};
    std::string head{""}, inflected{""}, parse{""};
    void clear()
    {
        head.clear();
        inflected.clear();
        parse.clear();
        id = 0;
        lesson = 0;
    }
} dbEntry;

class QuizItem : public visage::Frame
{
  public:
    std::string name_{""};
    visage::Font fontEn{20, visage::fonts::Lato_Regular_ttf};
    visage::Font fontGk{20, resources::fonts::GFSDidot_Regular_ttf};
    QuizItem();
    void draw(visage::Canvas &canvas);
    bool compareParses(std::string &userParse, std::string &dbParse);
    void clearAll();
    std::set<std::string> split(std::string &str, char delimiter);
    void check();       // is head correct, is parse?
    void readEntries(); // load input into fields
    void color();       // color entries by correctness
    void show();        // show first correct answer
    void mark();        // wrap it all up into one
    void red(visage::TextEditor *e);
    void grn(visage::TextEditor *e);
    void blk(visage::TextEditor *e);
    bool headIsCorrect{false}, parseIsCorrect{false};
    size_t idxOfCorrectParse{0};
    dbEntry userForm;             // full entry data for one question
    std::vector<dbEntry> dbForms; // for each user form, check for (legal) alts, push them in

    visage::Frame prompt, headword, parse;
    Label promptDb, headwordDb, parseDb;
    visage::TextEditor headwordUser, parseUser; // user entry

    friend std::ostream &operator<<(std::ostream &os, const QuizItem &point);
};

std::ostream &operator<<(std::ostream &os, const QuizItem &qi);

} // namespace gwr::gkqz
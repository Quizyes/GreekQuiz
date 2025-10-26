#pragma once

#include <visage/app.h>
#include "embedded/example_fonts.h"
#include "Label.h"
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include <visage_graphics/theme.h>

namespace gwr::gkqz
{

typedef struct dbEntry
{
    int id;
    std::string head, inflected, parse;
    void clear()
    {
        head.clear();
        inflected.clear();
        parse.clear();
    }
} dbEntry;

class QuizItem : public visage::Frame
{
  public:
    std::string name_{""};
    visage::Font fontEn{20, resources::fonts::Lato_Regular_ttf};
    visage::Font fontGk{20, resources::fonts::GFSDidot_Regular_ttf};
    QuizItem();
    void draw(visage::Canvas &canvas);
    void clearAll();
    void check();       // is head correct, is parse?
    void readEntries(); // load input into fields
    void color();       // color entries by correctness
    bool isCorrect{true};
    dbEntry userForm;             // full entry data for one question
    std::vector<dbEntry> dbForms; // for each user form, check for (legal) alts, push them in
    visage::TextEditor headwordUser, parseUser; // user entry

    Label promptDb, headwordDb, parseDb;

    visage::Frame prompt, headword, parse;

    friend std::ostream &operator<<(std::ostream &os, const QuizItem &point);
};

std::ostream &operator<<(std::ostream &os, const QuizItem &qi);

} // namespace gwr::gkqz
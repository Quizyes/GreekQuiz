#include "QuizItem.h"

using namespace visage::dimension;

namespace gwr::gkqz
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

std::ostream &operator<<(std::ostream &os, const QuizItem &qi)
{
    // os << "QuizItem(" << std::endl;
    // os << "userForm.id: \t" << 7 << std::endl;
    // os << "userForm.head: \t" << qi.userForm.head << std::endl;
    // os << "userForm.inflected: \t" << qi.userForm.inflected << std::endl;
    // os << "userForm.parse: \t" << qi.userForm.parse << std::endl;
    os << std::endl;
    os << "dbForms[0].id: \t" << qi.dbForms[0].id << std::endl;
    os << "dbForms[0].head: \t" << qi.dbForms[0].head << std::endl;
    os << "dbForms[0].inflected: \t" << qi.dbForms[0].inflected << std::endl;
    os << "dbForms[0].parse: \t" << qi.dbForms[0].parse << std::endl;
    os << std::endl;
    os << "entries with same inflected: " << qi.dbForms.size() << std::endl;
    os << ");" << std::endl;

    return os;
}

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

    headwordDb.setFont(fontGk.withSize(30.f));
    headwordDb.layout().setDimensions(100_vw, 100_vh);
    headwordDb.layout().setMargin(1_vh);

    for (auto &fr : {&headwordUser, &parseUser})
    {
        fr->setFont(fontGk.withSize(20.f));
        fr->setJustification(visage::Font::Justification::kCenter);
        fr->layout().setDimensions(100_vw, 49_vh);
        fr->setTextFieldEntry();
    }
    headwordUser.setDefaultText("headword");
    parseUser.setDefaultText("parse");

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
    for (auto &dbForm : dbForms)
    {
        if (userForm.head == dbForm.head)
            headIsCorrect = true;
        if (compareParses(userForm.parse, dbForm.parse))
            parseIsCorrect = true;
    }
    // compare userForms with dbForms
    // color fields
}

void QuizItem::show() { headwordDb.setText(dbForms[0].head); }

void QuizItem::readEntries()
{
    userForm.head = headwordUser.text().toUtf8();
    userForm.parse = parseUser.text().toUtf8();
}

void QuizItem::color()
{
    if (headIsCorrect)
        headwordUser.setBackgroundColorId(RIGHT);
    else
        headwordUser.setBackgroundColorId(WRONG);
    if (parseIsCorrect)
        parseUser.setBackgroundColorId(RIGHT);
    else
        parseUser.setBackgroundColorId(WRONG);
    redraw();
}

void QuizItem::clearAll()
{
    headwordUser.clear();
    parseUser.clear();
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
    return (matches == dbParts.size());
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
#include "Conj.h"

using namespace visage::dimension;

namespace gwr::gkqz
{

std::ostream &operator<<(std::ostream &os, const QuizItem &qi)
{
    os << "QuizItem(" << std::endl;
    os << "userForm.id: \t" << qi.userForm.id << std::endl;
    os << "userForm.head: \t" << qi.userForm.head << std::endl;
    os << "userForm.inflected: \t" << qi.userForm.inflected << std::endl;
    os << "userForm.parse: \t" << qi.userForm.parse << std::endl;
    os << ");" << std::endl;

    return os;
}

QuizItem::QuizItem()
{
    setFlexLayout(true);
    layout().setFlexRows(false);
    addChild(prompt, true);
    addChild(headword, true);
    addChild(parse, true);
    layout().setPadding(2.f);

    headword.layout().setFlexRows(true);
    headword.layout().setPaddingLeft(5.f);
    parse.layout().setFlexRows(true);
    parse.layout().setPaddingLeft(5.f);
    parse.layout().setDimensions(60_vw, 100_vh);

    for (auto &fr : {&headword, &prompt})
    {
        fr->setFlexLayout(true);
        fr->layout().setDimensions(25_vw, 100_vh);
    }

    headword.addChild(headwordUser, true);
    headword.addChild(headwordDb, true);

    parse.addChild(parseUser, true);
    parse.addChild(parseDb, true);

    prompt.addChild(promptDb, true);
    promptDb.layout().setDimensions(100_vw, 100_vh);
    promptDb.setFont(fontGk.withSize(35.f));
    headwordDb.setFont(fontGk.withSize(35.f));
    headwordDb.layout().setDimensions(100_vw, 100_vh);

    for (auto &fr : {&headwordUser, &parseUser})
    {
        fr->setFont(fontGk.withSize(20.f));
        fr->setJustification(visage::Font::Justification::kCenter);
        fr->layout().setDimensions(95_vw, 48_vh);
        fr->setTextFieldEntry();
    }
    headwordUser.setDefaultText("headword");
    parseUser.setDefaultText("parse");

    headwordDb.layout().setDimensions(95_vw, 48_vh);
    parseDb.layout().setDimensions(95_vw, 48_vh);

    promptDb.outline = true;
    headwordDb.outline = true;
    parseDb.outline = true;
}

void QuizItem::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xff000000);
    // canvas.rectangleBorder(0, 0, width(), height(), 1.0f);
}

void QuizItem::check()
{
    // compare userForms with dbForms
    // color fields
}

void QuizItem::readEntries()
{
    userForm.head = headwordUser.text().toUtf8();
    userForm.parse = parseUser.text().toUtf8();
}

void QuizItem::color() {}

void QuizItem::clearAll()
{
    for (size_t i = 0; i < 6; ++i)
    {
        headwordUser.clear();
        parseUser.clear();
    }
}

} // namespace gwr::gkqz
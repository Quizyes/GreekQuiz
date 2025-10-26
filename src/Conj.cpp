#include "Conj.h"

using namespace visage::dimension;

namespace gwr::gkqz
{

Conjugation::Conjugation()
{
    setFlexLayout(true);
    layout().setFlexRows(false);
    addChild(prompt, true);
    addChild(headword, true);
    addChild(parse, true);
    layout().setPadding(5.f);

    headword.layout().setFlexRows(true);
    headword.layout().setPadding(2.f);
    parse.layout().setFlexRows(true);
    parse.layout().setPadding(2.f);

    for (auto &fr : {&headword, &prompt})
    {
        fr->setFlexLayout(true);
        fr->layout().setDimensions(25_vw, 100_vh);
    }
    parse.layout().setDimensions(60_vw, 100_vh);

    headword.addChild(headwordUser, true);
    headword.addChild(headwordDb, true);

    parse.addChild(parseUser, true);
    parse.addChild(parseDb, true);

    for (auto &fr : {&headwordUser, &parseUser})
    {
        fr->setFont(fontGk.withSize(20.f));
        fr->setJustification(visage::Font::Justification::kCenter);
        fr->layout().setDimensions(95_vw, 50_vh);
        fr->setTextFieldEntry();
    }
    headwordUser.setDefaultText("headword");
    parseUser.setDefaultText("parse");

    promptDb.outline = true;
    headwordDb.outline = true;
    parseDb.outline = true;
}

void Conjugation::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xff000000);
    canvas.rectangleBorder(0, 0, width(), height(), 1.0f);
}

void Conjugation::check()
{
    // compare userForms with dbForms
    // color fields
}

void Conjugation::readEntries()
{
    userForm.head = headwordUser.text().toUtf8();
    userForm.parse = parseUser.text().toUtf8();
}

void Conjugation::color() {}

void Conjugation::clearAll()
{
    for (size_t i = 0; i < 6; ++i)
    {
        headwordUser.clear();
        parseUser.clear();
    }
}

} // namespace gwr::gkqz
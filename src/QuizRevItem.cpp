#include "QuizRevItem.h"
#include <iostream>

using namespace visage::dimension;
using bc = Betacode;

namespace gwr::gkrv
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

QuizRevItem::QuizRevItem()
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

    headword.addChild(&headwordDb, true);

    parse.addChild(&parseDb, true);

    prompt.addChild(&inflectedEditor, true);
    prompt.addChild(&inflectedDb, true);
    prompt.layout().setMargin(1_vh);

    inflectedDb.setFont(fontGk.withSize(25.f));
    inflectedDb.layout().setDimensions(100_vw, 49_vh);
    // inflectedDb.layout().setMargin(1_vh);
    inflectedDb.just = visage::Font::Justification::kLeft;

    inflectedEditor.setFont(fontGk.withSize(25.f));
    inflectedEditor.layout().setDimensions(100_vw, 49_vh);
    inflectedEditor.layout().setMargin(1_vh);
    inflectedEditor.setDefaultText("inflected...");
    inflectedEditor.setTextFieldEntry();
    inflectedEditor.onTextChange() = [&]() {
        inflectedDb.setText(bc::beta2greek(inflectedEditor.text().toUtf8()));
    };

    headwordDb.setFont(fontGk.withSize(35.f));
    headwordDb.layout().setDimensions(100_vw, 100_vh);
    headwordDb.layout().setMargin(1_vh);
    headwordDb.just = visage::Font::Justification::kCenter;

    inflectedEditor.onTextChange() += [&]() {
        // mirror betacode with Greek
        inflectedDb.setText(bc::beta2greek(inflectedEditor.text().toUtf8()));
    };

    headwordDb.layout().setDimensions(100_vw, 100_vh);
    parseDb.setFont(fontEn.withSize(30.f));
    parseDb.layout().setDimensions(100_vw, 100_vh);
    parseDb.layout().setMargin(1_vh);
    parseDb.just = visage::Font::Justification::kCenter;

    inflectedDb.outline = true;
    headwordDb.outline = true;
    parseDb.outline = true;
    userForm.id = 0;
    userForm.lesson = 0;
    userForm.head = "0";
    userForm.inflected = "0";
    userForm.parse = "0";
    // readEntries();
}

void QuizRevItem::draw(visage::Canvas &canvas) { canvas.setColor(0xff000000); }

void QuizRevItem::check()
{
    if (dbForm.inflected == userForm.inflected)
        inflectedIsCorrect = true;
    else
        inflectedIsCorrect = false;
}

void QuizRevItem::show()
{
    inflectedEditor.setText(bc::beta2greek(inflectedEditor.text().toUtf8()));
    inflectedDb.setText(bc::beta2greek(dbForm.inflected));
}

void QuizRevItem::mark()
{
    readEntries();
    check();
    color();
    show();
    redraw();
}

void QuizRevItem::red(visage::TextEditor *e)
{
    e->setBackgroundColorId(WRONG);
    e->redraw();
}

void QuizRevItem::grn(visage::TextEditor *e)
{
    e->setBackgroundColorId(RIGHT);
    e->redraw();
}

void QuizRevItem::blk(visage::TextEditor *e)
{
    e->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    e->redraw();
}

void QuizRevItem::readEntries() { userForm.inflected = inflectedEditor.text().toUtf8(); }

void QuizRevItem::color()
{
    if (inflectedIsCorrect)
        grn(&inflectedEditor);
    else
        red(&inflectedEditor);
    redraw();
}

void QuizRevItem::clearAll()
{
    inflectedEditor.clear();
    headwordDb.setText("");
    parseDb.setText("");
    inflectedEditor.setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    redraw();
    // set colors
}

} // namespace gwr::gkrv
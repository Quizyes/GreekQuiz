#include "App.h"

#define QLOG(msg) std::cerr << "DEBUG: " << msg << std::endl;

using namespace visage::dimension;

namespace gwr::gkqz
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

App::App() : dbm(":memory:")
{
    setFlexLayout(true);
    layout().setFlexRows(true);
    addChild(header, true);
    addChild(body, true);
    header.setFlexLayout(true);
    header.layout().setDimensions(100_vw, 10_vh);
    header.layout().setFlexRows(false);
    header.layout().setFlexGap(1_vw);
    header.layout().setPadding(8_vh);
    header.outline = false;

    header.addChild(newBtn, true);
    header.addChild(lesson, true);
    header.addChild(markBtn, true);

    newBtn.layout().setDimensions(25_vw, 100_vh);
    lesson.layout().setDimensions(35_vw, 100_vh);
    markBtn.layout().setDimensions(25_vw, 100_vh);

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { markQuiz(); };

    lesson.setFont(font.withSize(25.f));
    lesson.onEnterKey() = [this]() {
        auto head = lesson.text().toInt();
        newQuiz(head);
    };
    // ============================

    body.setFlexLayout(true);
    body.layout().setFlexRows(true);
    body.layout().setDimensions(100_vw, 98_vh);
    body.layout().setFlexGap(5.f);
    body.outline = false;

    body.addChild(c1, true);
    body.addChild(c2, true);
    body.addChild(c3, true);
    body.addChild(c4, true);
    body.addChild(c5, true);
    c1.layout().setDimensions(95_vw, 18_vh);
    c2.layout().setDimensions(95_vw, 18_vh);
    c3.layout().setDimensions(95_vw, 18_vh);
    c4.layout().setDimensions(95_vw, 18_vh);
    c5.layout().setDimensions(95_vw, 18_vh);
    cs[0] = &c1;
    cs[1] = &c2;
    cs[2] = &c3;
    cs[3] = &c4;
    cs[4] = &c5;
}

void App::newQuiz() { newQuiz(2); }

void App::newQuiz(int lessonNum)
{
    QLOG("made it to newquiz(int)")
    clearColors();
    QLOG("cleared colors")

    auto st = dbm.getStmt("select * from morphs where lesson <= ? order by random() limit 5");
    st.bind(1, lessonNum);
    QLOG("bound query")

    size_t i{0};
    while (st.executeStep())
    {
        QLOG("step")
        dbEntry d;
        d.id = st.getColumn("id").getInt();
        d.inflected = st.getColumn("inflected").getString();
        d.head = st.getColumn("head").getString();
        d.parse = st.getColumn("parse").getString();
        cs[i]->dbForms.push_back(d);
        cs[i]->promptDb.setText(d.inflected);
        ++i;
    }

    userInputIsShown = true;
    quizIsMarked = false;
    redraw();
}

void App::markQuiz()
{
    if (!userInputIsShown)
        return;
    readContents();
    clearColors();

    // compare userForms with dbForms
    for (auto &conj : cs)
    {
        conj->check();
    }

    // color fields by correctness
    userInputIsShown = true;
    quizIsMarked = true;
    color();
    redraw();
}

void App::readContents()
{
    for (auto conj : cs)
    {
        conj->readEntries();
    }
}

void App::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xffbbbbbb);
    canvas.fill(0, 0, width(), height());
}

void App::clearColors()
{
    QLOG("clearing colors")
    for (auto conj : cs)
    {
        QLOG("clearing one pair")
        QLOG("conj: " << conj)
        QLOG("headword: " << conj->headwordUser.text().toUtf8())
        conj->headwordUser.setBackgroundColorId(visage::TextEditor::TextEditorBackground);
        conj->parseUser.setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    }
    redraw();
}

void App::red(Label *l)
{
    l->setColor(visage::Color(0xffbb3232));
    l->redraw();
}
void App::red(visage::TextEditor *e)
{
    e->setBackgroundColorId(WRONG);
    e->redraw();
}

void App::grn(Label *l)
{
    l->setColor(visage::Color(0xff32bb32));
    l->redraw();
}
void App::grn(visage::TextEditor *e)
{
    e->setBackgroundColorId(RIGHT);
    e->redraw();
}

void App::blk(Label *l)
{
    l->setColor(visage::Color(0xff000000));
    l->redraw();
}
void App::blk(visage::TextEditor *e)
{
    e->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    e->redraw();
}

void App::color()
{
    for (auto conj : cs)
    {
        conj->color();
        conj->redraw();
    }
}

} // namespace gwr::gkqz
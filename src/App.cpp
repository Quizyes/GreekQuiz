#include "App.h"

#define QLOG(msg) std::cerr << "DEBUG: " << msg << std::endl;

using namespace visage::dimension;
using bc = Betacode;

namespace gwr::gkqz
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

App::App() : dbm(":memory:")
{
    setFlexLayout(true);
    layout().setFlexRows(true);
    addChild(&header, true);
    addChild(&body, true);
    header.setFlexLayout(true);
    header.layout().setDimensions(100_vw, 10_vh);
    header.layout().setFlexRows(false);
    header.layout().setFlexGap(1_vw);
    header.layout().setPadding(8_vh);
    // header.layout().setMargin(2.f);

    header.outline = false;

    header.addChild(newBtn, true);
    header.addChild(lesson, true);
    header.addChild(markBtn, true);

    newBtn.layout().setDimensions(33_vw, 100_vh);
    lesson.layout().setDimensions(32_vw, 100_vh);
    markBtn.layout().setDimensions(33_vw, 100_vh);

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
        int head = lesson.text().toInt();
        if (head > 1)
            newQuiz(head);
        else
            newQuiz();
    };

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
    body.layout().setMargin(5.f);
    body.outline = false;

    body.addChild(c1, true);
    body.addChild(c2, true);
    body.addChild(c3, true);
    body.addChild(c4, true);
    body.addChild(c5, true);
    c1.layout().setDimensions(99_vw, 18_vh);
    c2.layout().setDimensions(99_vw, 18_vh);
    c3.layout().setDimensions(99_vw, 18_vh);
    c4.layout().setDimensions(99_vw, 18_vh);
    c5.layout().setDimensions(99_vw, 18_vh);
    cs[0] = &c1;
    cs[1] = &c2;
    cs[2] = &c3;
    cs[3] = &c4;
    cs[4] = &c5;
}

void App::newQuiz() { newQuiz(2); }

void App::newQuiz(int lessonNum)
{
    clearColors();
    lessonNum = std::clamp(lessonNum, 2, 20);
    lesson.setText(lessonNum);
    auto st =
        dbm.getStmt("select id, inflected, head, parse, lesson from morphs where lesson <= ? order "
                    "by random() limit 5");
    st.bind(1, lessonNum);

    for (size_t j = 0; j < 5; ++j)
    {
        cs[j]->dbForms.clear();
        cs[j]->clearAll();
    }

    size_t i{0};
    while (st.executeStep())
    {
        dbEntry d;
        d.id = st.getColumn("id").getInt();
        d.head = st.getColumn("head").getString();
        d.inflected = st.getColumn("inflected").getString();
        d.parse = st.getColumn("parse").getString();
        d.lesson = st.getColumn("lesson").getInt();
        cs[i]->dbForms.push_back(d);
        cs[i]->promptDb.setText(bc::beta2greek(d.inflected));
        ++i;
    }

    getAlts();

    // std::cout << *(cs[i]);

    userInputIsShown = true;
    quizIsMarked = false;
    redraw();
}

void App::getAlts()
{
    for (size_t i = 0; i < 5; ++i)
    {
        std::vector<dbEntry> alts;
        dbEntry root;
        root.id = cs[i]->dbForms[0].id;
        root.head = cs[i]->dbForms[0].head;
        root.inflected = cs[i]->dbForms[0].inflected;
        root.parse = cs[i]->dbForms[0].parse;
        auto st = dbm.getStmt("select * from morphs where inflected = ?");
        st.bind(1, root.inflected);
        while (st.executeStep())
        {
            dbEntry d;
            d.id = st.getColumn("id").getInt();
            d.head = st.getColumn("head").getString();
            d.inflected = st.getColumn("inflected").getString();
            d.parse = st.getColumn("parse").getString();
            d.lesson = st.getColumn("lesson").getInt();
            alts.push_back(d);
            // printDbEntry(d);
        }
        for (auto &alt : alts)
        {
            cs[i]->dbForms.push_back(alt);
        }
    }
}

void App::markQuiz()
{
    if (!userInputIsShown)
        return;
    for (auto &conj : cs)
    {
        conj->mark();
        conj->redraw();
    }
    userInputIsShown = true;
    quizIsMarked = true;
    redraw();
}

void App::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xffbbbbbb);
    canvas.fill(0, 0, width(), height());
}

void App::clearColors()
{
    for (auto conj : cs)
    {
        blk(&(conj->headwordUser));
        blk(&(conj->parseUser));
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

void App::printDbEntry(dbEntry entry)
{
    std::cout << "dbEntry(" << std::endl;
    std::cout << "entry.id:\t" << entry.id << std::endl;
    std::cout << "entry.head:\t" << entry.head << std::endl;
    std::cout << "entry.inflected:\t" << entry.inflected << std::endl;
    std::cout << "entry.parse:\t" << entry.parse << std::endl;
    std::cout << "entry.lesson:\t" << entry.lesson << std::endl;
    std::cout << ")" << std::endl;
}

} // namespace gwr::gkqz
#include "App.h"

#define QLOG(msg) std::cerr << "DEBUG: " << msg << std::endl;

using namespace visage::dimension;
using bc = Betacode;

namespace gwr::gkqz
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

App::~App()
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        delete qis[i];
    }
}

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

    header.addChild(lessonLabel);
    header.addChild(lesson);
    header.addChild(newBtn);
    header.addChild(markBtn);
    header.addChild(helpBtn);
    header.addChild(reverseBtn);

    lessonLabel.layout().setDimensions(8_vw, 100_vh);
    lesson.layout().setDimensions(5_vw, 100_vh);
    newBtn.layout().setDimensions(11_vw, 100_vh);
    markBtn.layout().setDimensions(11_vw, 100_vh);
    helpBtn.layout().setDimensions(5_vw, 100_vh);
    reverseBtn.layout().setDimensions(9_vw, 100_vh);

    lessonLabel.setText("Lesson #");
    lessonLabel.setFont(font.withSize(20.f));
    lessonLabel.outline = false;
    lessonLabel.just = visage::Font::Justification::kCenter;

    lesson.setFont(font.withSize(20.f));
    lesson.onEnterKey() = [this]() {
        auto head = lesson.text().toInt();
        newQuiz(head);
    };
    lesson.setText("2");

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
        auto text = lesson.text();
        if (text.isEmpty())
            newQuiz();
        else
            newQuiz(text.toInt());
    };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { markQuiz(); };

    helpBtn.setFont(font.withSize(25.f));
    helpBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
        // clang-format off
        EM_ASM(window.open("help.html", "myPopup", "width=1200,height=900,resizable=yes,scrollbars=yes,location=no,menubar=no,toolbar=no,status=no"));
        // clang-format on
    };

    reverseBtn.setFont(font.withSize(25.f));
    reverseBtn.onMouseDown() = [&](const visage::MouseEvent &e) { switchQs(); };

    // ============================

    body.setFlexLayout(true);
    body.layout().setFlexRows(true);
    body.layout().setDimensions(100_vw, 98_vh);
    body.layout().setMargin(5.f);
    body.outline = false;

    for (int i = 0; i < MAX_ROWS; ++i)
    {
        auto qi = new QuizItem();
        auto qr = new gwr::gkrv::QuizRevItem();
        qi->layout().setDimensions(99_vw, 11_vh);
        qr->layout().setDimensions(99_vw, 11_vh);
        qis[i] = qi;
        qrs[i] = qr;
        body.addChild(qi);
    }
}

void App::newQuiz() { newQuiz(2); }

void App::newQuiz(int lessonNum)
{
    clearColors();
    lessonNum = std::clamp(lessonNum, 2, 20);
    lesson.setText(lessonNum);

    // pass off query and marking logic to quizitem??
    // or do the switch in here?

    // clear colors and contents
    for (size_t j = 0; j < MAX_ROWS; ++j)
    {
        if (!isReverse)
        {
            qis[j]->dbForms.clear();
            qis[j]->clearAll();
        }
        else
        {
            qrs[j]->dbForm.clear();
            qrs[j]->clearAll();
        }
    }

    // getQuery
    auto st = dbm.getStmt(
        "select id, inflected, head, parse, lesson from newmorphs where lesson <= ? order "
        "by random() limit ?");
    st.bind(1, lessonNum);
    st.bind(2, MAX_ROWS);

    // loadResults
    if (!isReverse)
    {
        size_t i{0};
        while (st.executeStep())
        {
            dbEntry d;
            d.id = st.getColumn("id").getInt();
            d.head = st.getColumn("head").getString();
            d.inflected = st.getColumn("inflected").getString();
            d.parse = st.getColumn("parse").getString();
            d.lesson = st.getColumn("lesson").getInt();
            qis[i]->dbForms.push_back(d);
            qis[i]->promptDb.setText(bc::beta2greek(d.inflected));
            ++i;
        }
        getAlts();
    }
    else
    {
        size_t i{0};
        while (st.executeStep())
        {
            dbEntry d;
            d.id = st.getColumn("id").getInt();
            d.head = st.getColumn("head").getString();
            d.inflected = st.getColumn("inflected").getString();
            d.parse = st.getColumn("parse").getString();
            d.lesson = st.getColumn("lesson").getInt();
            qrs[i]->dbForm = d;
            qrs[i]->headwordDb.setText(bc::beta2greek(d.head));
            qrs[i]->parseDb.setText(d.parse);
            ++i;
        }
    }

    userInputIsShown = true;
    quizIsMarked = false;
    redraw();
}

void App::getAlts()
{
    for (size_t i = 0; i < MAX_ROWS; ++i)
    {
        std::vector<dbEntry> alts;
        dbEntry root;
        root.id = qis[i]->dbForms[0].id;
        root.head = qis[i]->dbForms[0].head;
        root.inflected = qis[i]->dbForms[0].inflected;
        root.parse = qis[i]->dbForms[0].parse;
        auto st = dbm.getStmt("select * from newmorphs where inflected = ? and parse != ?");
        st.bind(1, root.inflected);
        st.bind(2, root.parse);
        while (st.executeStep())
        {
            dbEntry d;
            d.id = st.getColumn("id").getInt();
            d.head = st.getColumn("head").getString();
            d.inflected = st.getColumn("inflected").getString();
            d.parse = st.getColumn("parse").getString();
            d.lesson = st.getColumn("lesson").getInt();
            alts.push_back(d);
        }
        for (auto &alt : alts)
        {
            qis[i]->dbForms.push_back(alt);
        }
    }
}

void App::markQuiz()
{
    if (!userInputIsShown)
        return;
    if (!isReverse)
    {
        for (auto &conj : qis)
        {
            conj->mark();
            conj->redraw();
        }
    }
    else
    {
        for (auto &qr : qrs)
        {
            qr->mark();
            qr->redraw();
        }
    }
    userInputIsShown = true;
    quizIsMarked = true;
    redraw();
}

void App::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xffcccccc);
    canvas.fill(0, 0, width(), height());
}

void App::clearColors()
{
    for (auto conj : qis)
        conj->clearAll();
    for (auto qr : qrs)
        qr->clearAll();
    redraw();
}

void App::switchQs()
{
    body.removeAllChildren();
    if (isReverse)
    {
        for (auto qi : qis)
        {
            body.addChild(qi);
        }
    }
    else
    {
        for (auto qr : qrs)
        {
            body.addChild(qr);
        }
    }
    isReverse = !isReverse;
    redraw();
}

} // namespace gwr::gkqz
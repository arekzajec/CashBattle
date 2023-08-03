#include "OperatorPanel.hpp"
#include "GEngine.hpp"

QLabel * QStatePanel::newQLabel(QString str, QFont font) {
    QLabel * ans = new QLabel(str,this);
    ans->setAlignment(Qt::AlignCenter);
    ans->setFont(font);
    return ans;
}

QStatePanel::QStatePanel (QWidget * parent,QStatePanelLocInterface * loc, QFont font) : QWidget(parent) {
    mainlayout = new QVBoxLayout(this);
    qstates.push_back(newQLabel(loc->strState(),font));
    qstates.push_back(newQLabel(loc->strDeactivated(),font));
    qstates.push_back(newQLabel(loc->strPunishment(),font));
    qstates.push_back(newQLabel(loc->strCategory(),font));
    qstates.push_back(newQLabel(loc->strExtraPot(),font));
    qstates.push_back(newQLabel(loc->strTip(),font));
    qstates.push_back(newQLabel(loc->strLicitationStart(),font));
    qstates.push_back(newQLabel(loc->strLicitation(),font));
    qstates.push_back(newQLabel(loc->strLicitationBlock(),font));
    qstates.push_back(newQLabel(loc->strSold(),font));
    qstates.push_back(newQLabel(loc->strMusical(),font));
    qstates.push_back(newQLabel(loc->strQuestion(),font));
    qstates.push_back(newQLabel(loc->strEnd(),font));
    for(auto & x : qstates)
        mainlayout->addWidget(x);
}

void QStatePanel::refresh(state current_state, bool is_any_team_va_banque) {
    qstates[0]->setStyleSheet("QLabel {background-color : lightgrey; color : black; }");
    qstates[1]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::idle ? "white":"lightgrey")+"; color : black; }");
    qstates[2]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::punishment ? "white":"lightgrey")+"; color : black; }");
    qstates[3]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::category ? "white":"lightgrey")+"; color : black; }");
    qstates[4]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::extra_pot ? "white":"lightgrey")+"; color : black; }");
    qstates[5]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::tip_buy ? "white":"lightgrey")+"; color : black; }");
    qstates[6]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::start_lic ? "white":"lightgrey")+"; color : black; }");
    qstates[7]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::lic && !is_any_team_va_banque ? "white":"lightgrey")+"; color : black; }");
    qstates[8]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::lic && is_any_team_va_banque ? "white":"lightgrey")+"; color : black; }");
    qstates[9]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::sold ? "white":"lightgrey")+"; color : black; }");
    qstates[10]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::music_question ? "white":"lightgrey")+"; color : black; }");
    qstates[11]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::question ? "white":"lightgrey")+"; color : black; }");
    qstates[12]->setStyleSheet("QLabel {background-color :"+QString(current_state == state::end ? "white":"lightgrey")+"; color : black; }");
}

QButtonDesc::QButtonDesc(QWidget * parent, QFont font, double scale) : QWidget(parent) {
    mainlayout = new QHBoxLayout(this);
    qbutton = new QPushButton(this);
    qbutton->setFont(font);
    qbutton->setEnabled(false);
    qbutton->setMinimumWidth(100*scale);
    qbutton->setMaximumWidth(100*scale);
    qbutton->setMinimumHeight(45*scale);
    qdesc = new QLabel("",this);
    qdesc->setAlignment(Qt::AlignLeft);
    qdesc->setFont(font);
    mainlayout->addWidget(qbutton);
    mainlayout->addWidget(qdesc);

    QObject::connect(qbutton,&QPushButton::released,this,&QButtonDesc::released_signal);
}

QButtonDesc::QButtonDesc(QWidget * parent, QFont font, QString str, double scale) : QButtonDesc(parent,font,scale) {
    qbutton->setText(str);
}

QButtonDesc::QButtonDesc(QWidget * parent, QFont font, QIcon ico, double scale) : QButtonDesc(parent,font,scale) {
    qbutton->setIcon(ico);
    qbutton->setIconSize(QSize(35*scale,35*scale));
}

void QButtonDesc::refresh() {
    qbutton->update();
    qdesc->update();
}

QButtonDescGroup::QButtonDescGroup(QWidget * parent, QButtonDescGroupLocInterface * localization, GEngine * _gengine, QFont font, double scale) : QWidget(parent), loc(localization), gengine(_gengine) {
    mainlayout = new QVBoxLayout(this);
    qdesc = new QLabel("Przyciski");
    qdesc->setAlignment(Qt::AlignCenter);
    qdesc->setFont(font);
    mainlayout->addWidget(qdesc);
    qbuttons.push_back(new QButtonDesc(this,font,style()->standardIcon(QStyle::SP_ArrowUp),scale));
    qbuttons.push_back(new QButtonDesc(this,font,style()->standardIcon(QStyle::SP_ArrowDown),scale));
    qbuttons.push_back(new QButtonDesc(this,font,style()->standardIcon(QStyle::SP_DialogOkButton),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("P"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("E"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("Z"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("X"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("C"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("A"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("D"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("H"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("S"),scale));
    qbuttons.push_back(new QButtonDesc(this,font,QString("U"),scale));
    for (auto & x : qbuttons) {
        mainlayout->addWidget(x);
        QObject::connect(x,&QButtonDesc::released_signal,this,&QButtonDescGroup::released_slot);
    }
    refresh();
}

void QButtonDescGroup::released_slot() {
    ekey key = ekey::unknown;
    int i=0;
    for (i=0;i<qbuttons.size();++i) {
        if (qbuttons[i] == sender()) {
            break;
        }
    }
    switch (i) {
        case 0: key = ekey::up;break;
        case 1: key = ekey::down;break;
        case 2: key = ekey::enter;break;
        case 3: key = ekey::p;break;
        case 4: key = ekey::e;break;
        case 5: key = ekey::z;break;
        case 6: key = ekey::x;break;
        case 7: key = ekey::c;break;
        case 8: key = ekey::a;break;
        case 9: key = ekey::d;break;
        case 10: key = ekey::h;break;
        case 11: key = ekey::s;break;
        case 12: key = ekey::u;break;

    }
    released_signal(key);
}

void QButtonDescGroup::setButtonsEnabled(const std::initializer_list<int> & args) {
    for (auto & x : args)
        qbuttons[x]->setButtonEnabled(true);
}

void QButtonDescGroup::setLabelText(int ind, QString str) {
    if (ind >= 0 && ind < qbuttons.size())
        qbuttons[ind]->setLabelText(str);
}

void QButtonDescGroup::licitation_disp(Team * ateam) {
    for (int i=0;i<3;++i) {
        if (ateam == &(gengine->get_team(i))) {
            setButtonsEnabled({i+5}); //Z, X, C
            if (ateam->va_banque_val() == gengine->get_va_banque_tab_val(0))
                setLabelText(i+5,QString::fromStdString(gengine->get_team(i).get_name())+ loc->strVaBanque());
            else if (ateam->get_points_invested() > gengine->get_va_banque_tab_val(0) &&
                     ateam->va_banque_val() == gengine->get_va_banque_tab_val(1))
                setLabelText(i+5,QString::fromStdString(gengine->get_team(i).get_name())+ loc->strVaBanque());
            else if (ateam->get_points_invested() >= gengine->get_va_banque_tab_val(1))
                setLabelText(i+5,QString::fromStdString(gengine->get_team(i).get_name())+ loc->strVaBanque());
            else
                setLabelText(i+5,QString::fromStdString(gengine->get_team(i).get_name())+ loc->strBlocks());
        } else {
            if (gengine->get_team(i).va_banque_val() > ateam->get_points_invested() && 
                ateam->get_points_invested() != ateam->va_banque_val()) {
                setButtonsEnabled({i+5}); //Z, X, C
                setLabelText(i+5,QString::fromStdString(gengine->get_team(i).get_name()) + loc->strLeads());
            }
        }
    }
}

void QButtonDescGroup::refresh() {
    Team * ateam = nullptr;
    setAllButtonsDisabled();
    resetAllLabelText();
    state cs = gengine->get_current_state();
    switch (cs) {
        case state::idle : {
            setButtonsEnabled({2,3,4,10}); //Enter, P, E, T
            setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strCategory());
            setLabelText(3,loc->strGoTo()+loc->getQStateLoc()->strPunishment());
            setLabelText(4,loc->strForceBB());
            setLabelText(10,loc->strForceTip());
        };break;
        case state::punishment : {
            setButtonsEnabled({2,4,10}); //Enter, E, T
            setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strCategory());
            setLabelText(4,loc->strForceBB());
            setLabelText(10,loc->strForceTip());
            ateam = gengine->get_active_team();
            if (ateam) {
                for (int i=0;i<3;++i) {
                    if (ateam == &(gengine->get_team(i)) && gengine->get_maxpoints(i) > ateam->get_points()) {
                        setButtonsEnabled({0}); //Up
                        setLabelText(0,loc->strUp100Team() + QString::fromStdString(gengine->get_active_team()->get_name()));
                    }
                }
                if (ateam->get_points()) {
                    setButtonsEnabled({1}); //Down
                    setLabelText(1,loc->strDown100Team() + QString::fromStdString(gengine->get_active_team()->get_name()));
                }
                for (int i=0;i<3;++i) {
                    if (ateam != &(gengine->get_team(i)) && gengine->get_team(i).get_points()) {
                        setButtonsEnabled({i+5}); //Z, X, C
                        setLabelText(i+5,loc->strPickTeam() + QString::fromStdString(gengine->get_team(i).get_name()));
                    }
                }
            } else {
                for (int i=0;i<3;++i) {
                    if (gengine->get_team(i).get_points()) {
                        setButtonsEnabled({i+5}); //Z, X, C
                        setLabelText(i+5,loc->strPickTeam() + QString::fromStdString(gengine->get_team(i).get_name()));
                    }
                }
            }
        };break;
        case state::category : {
            setButtonsEnabled({2,4}); //Enter, E
            setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strLicitationStart());
            setLabelText(4,loc->strGoTo()+loc->getQStateLoc()->strExtraPot());
        };break;
        case state::extra_pot : {
            setButtonsEnabled({0,2}); //Up, Enter
            if (gengine->get_olddpot() > gengine->get_minoldpot()) {
                setButtonsEnabled({1}); //Down
                setLabelText(1,loc->strDown100Pot());
            }
            setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strLicitationStart());
            setLabelText(0,loc->strUp100Pot());
        };break;
        case state::tip_buy : {
            setButtonsEnabled({2}); //Enter
            setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strDeactivated());
            ateam = gengine->get_active_team();
            if (ateam) {
                if (ateam->get_points()) {
                    setButtonsEnabled({0}); //Up
                    setLabelText(0,loc->strUp100TeamLic() + QString::fromStdString(gengine->get_active_team()->get_name()));
                }
                if (ateam->get_points_invested() > gengine->get_old_highest_bid() + 100) {
                    setButtonsEnabled({1}); //Down
                    setLabelText(1,loc->strDown100TeamLic() + QString::fromStdString(gengine->get_active_team()->get_name()));
                }
                if(!gengine->is_any_team_va_banque())
                    licitation_disp(ateam);
            } else {
                for (int i=0;i<3;++i) {
                    if (gengine->get_team(i).get_points()) {
                        setButtonsEnabled({5,6,7}); //Z, X, C
                        setLabelText(i+5,QString::fromStdString(gengine->get_team(i).get_name()) + loc->strLeads());
                    }
                }
            }
        };break;
        case state::start_lic : {
            for (int i=0;i<3;++i) {
                if (gengine->get_team(i).va_banque_val() > 200) {
                    setButtonsEnabled({i+5}); //Z, X, C
                    setLabelText(i+5,QString::fromStdString(gengine->get_team(i).get_name())+ loc->strLeads());
                }
            }
        };break;
        case state::lic : {
            ateam = gengine->get_active_team();
            setButtonsEnabled({2}); //Enter
            setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strSold());
            if (ateam->get_points()) {
                setButtonsEnabled({0}); //Up
                setLabelText(0,loc->strUp100TeamLic() + QString::fromStdString(gengine->get_active_team()->get_name()));
            }
            if (ateam->get_points_invested() > gengine->get_old_highest_bid() + 100) {
                setButtonsEnabled({1}); //Down
                setLabelText(1,loc->strDown100TeamLic() + QString::fromStdString(gengine->get_active_team()->get_name()));
            }
            if (!gengine->is_any_team_va_banque())
                licitation_disp(ateam);
        };break;
        case state::sold : {
            setButtonsEnabled({2}); //Enter
            if (gengine->get_current_question().is_musical_q())
                setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strMusical());
            else
                setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strQuestion());
        };break;
        case state::music_question : {
            setButtonsEnabled({2}); //Enter
            setLabelText(2,loc->strGoTo()+loc->getQStateLoc()->strQuestion());
        };break;
        case state::question : {
            ateam = gengine->get_active_team();
            setButtonsEnabled({8,9,11}); //A, D, S
            if (ateam->get_points() < gengine->get_active_team_max_point()) {
                setButtonsEnabled({0}); //Up
                setLabelText(0,loc->strUp100Team() + QString::fromStdString(gengine->get_active_team()->get_name()));
            }
            if (ateam->get_points()) {
                setButtonsEnabled({1}); //Down
                setLabelText(1,loc->strDown100Team() + QString::fromStdString(gengine->get_active_team()->get_name()));
            }
            setLabelText(8,loc->strCorrectAnswer());
            setLabelText(9,loc->strIncorrectAnswer());
            if (!gengine->is_tips_visible()) {
                setButtonsEnabled({10}); //Tip
                setLabelText(10,loc->strShowTip());
            }
            if (gengine->is_timer_runnung())
                setLabelText(11,loc->strStopTime());
            else 
                setLabelText(11,loc->strStartTime());
        };break;
    }
    if (gengine->is_any_snap()) {
        setButtonsEnabled({12});
        setLabelText(12,loc->strUndo());
    }
    for (auto & x : qbuttons) {
        x->refresh();
    }
}

OperatorQuestionInfo::OperatorQuestionInfo(QWidget * parent, OperatorQuestionInfoLocInterface * localization, QFont font) : 
    QWidget(parent), loc(localization) {
    layout = new QVBoxLayout(this);
    ismusic = new QLabel(this);
    ismusic->setStyleSheet("QLabel {background-color : grey; color : black; }");
    ismusic->setWordWrap(true);
    ismusic->setFont(font);
    ismusic->setAlignment(Qt::AlignCenter);

    qquestion = new QLabel(this);
    qquestion->setStyleSheet("QLabel {background-color : grey; color : black; }");
    qquestion->setWordWrap(true);
    qquestion->setFont(font);
    qquestion->setAlignment(Qt::AlignCenter);

    qanswer = new QLabel(this);
    qanswer->setStyleSheet("QLabel {background-color : green; color : black; }");
    qanswer->setWordWrap(true);
    qanswer->setFont(font);
    qanswer->setAlignment(Qt::AlignCenter);

    qtip1 = new QLabel(this);
    qtip1->setStyleSheet("QLabel {background-color : red; color : black; }");
    qtip1->setWordWrap(true);
    qtip1->setFont(font);
    qtip1->setAlignment(Qt::AlignCenter);

    qtip2 = new QLabel(this);
    qtip2->setStyleSheet("QLabel {background-color : red; color : black; }");
    qtip2->setWordWrap(true);
    qtip2->setFont(font);
    qtip2->setAlignment(Qt::AlignCenter);

    qtip3 = new QLabel(this);
    qtip3->setStyleSheet("QLabel {background-color : red; color : black; }");
    qtip3->setWordWrap(true);
    qtip3->setFont(font);
    qtip3->setAlignment(Qt::AlignCenter);

    layout->addWidget(ismusic);
    layout->addWidget(qquestion);
    layout->addWidget(qanswer);
    layout->addWidget(qtip1);
    layout->addWidget(qtip2);
    layout->addWidget(qtip3);
}

void OperatorQuestionInfo::replace_question(const Question & q) {
    if (q.is_musical_q()) {
        ismusic->setText(loc->strMusical());
        ismusic->setStyleSheet("QLabel {background-color : orange; color : black; }");
    } else {
        ismusic->setText(loc->strRegular());
        ismusic->setStyleSheet("QLabel {background-color : grey; color : black; }");
    }
    qquestion->setText(QString::fromStdString(q.get_question()));
    qanswer->setText(QString::fromStdString(q.get_answer()));
    qtip1->setText(QString::fromStdString(q.get_tips()[0]));
    qtip2->setText(QString::fromStdString(q.get_tips()[1]));
    qtip3->setText(QString::fromStdString(q.get_tips()[2]));
    qquestion->update();
    qanswer->update();
    qtip1->update();
    qtip2->update();
    qtip3->update();
}

OperatorPanel::OperatorPanel(OperatorPanelLocInterface * localization, GameWindow * _gwindow, GEngine * _gengine, double scale) : 
        loc(localization),
        gwindow(_gwindow), 
        gengine(_gengine) 
{
    this->setStyleSheet("QWidget { background-color : lightgrey;}");
    
    QFont font("Arial",20*scale);

    mainlayout = new QHBoxLayout(this);
    qstatepanel = new QStatePanel(this,loc->getQStateLoc(),font);
    qbuttons = new QButtonDescGroup(this,loc->getQButtonLoc(),gengine,font,scale);
    rightlayout = new QVBoxLayout();
    qlocalgamew = new GameWindow(loc->getGameWinLoc(),*gengine, 0.35*scale, false, true);
    qquest = new OperatorQuestionInfo(this,loc->getOperQInfLoc(),font);
    mainlayout->addWidget(qstatepanel);
    mainlayout->addWidget(qbuttons);
    mainlayout->addLayout(rightlayout);
    mainlayout->setStretch(0, 1);
    mainlayout->setStretch(1, 1);
    mainlayout->setStretch(2, 1);
    rightlayout->addWidget(qlocalgamew);
    rightlayout->addWidget(qquest);
    rightlayout->setStretch(0,1);
    rightlayout->setStretch(1,1);

    QObject::connect(qbuttons,&QButtonDescGroup::released_signal,this,&OperatorPanel::qbuttonhandler);

    refresh();
}

void OperatorPanel::qbuttonhandler(ekey key) {
    send2engine_and_refresh(key);
}

void OperatorPanel::refresh() {
    state cs = gengine->get_current_state();
    bool ivabq = gengine->is_any_team_va_banque();
    qstatepanel->refresh(cs,ivabq);
    qbuttons->refresh();
    qlocalgamew->refresh();
    if (cs == state::category)
        qquest->replace_question(gengine->get_current_question());
    update();
}

void OperatorPanel::send2engine_and_refresh(ekey key) {
    state old_state = gengine->get_current_state();
    gengine->perform_action(key);
    if ((key == ekey::enter || key == ekey::e || key == ekey::h) 
         && (old_state == state::idle || old_state == state::punishment )) 
    {
        gwindow->cat_rand_animation();
    }
    gwindow->refresh();
    refresh();
}

void OperatorPanel::keyPressEvent(QKeyEvent *event) 
{
    int qkey = event->key();
    ekey key = ekey::unknown;
    switch (qkey) {
        case Qt::Key_Enter : key = ekey::enter;break;
        case Qt::Key_Return : key = ekey::enter;break;
        case Qt::Key_Z : key = ekey::z;break;
        case Qt::Key_X : key = ekey::x;break;
        case Qt::Key_C : key = ekey::c;break;
        case Qt::Key_Up : key = ekey::up;break;
        case Qt::Key_Down : key = ekey::down;break;
        case Qt::Key_H : key = ekey::h;break;
        case Qt::Key_A : key = ekey::a;break;
        case Qt::Key_D : key = ekey::d;break;
        case Qt::Key_P : key = ekey::p;break;
        case Qt::Key_E : key = ekey::e;break;
        case Qt::Key_S : key = ekey::s;break;
        case Qt::Key_U : key = ekey::u;break;
    }
    event->ignore();
    send2engine_and_refresh(key);
}
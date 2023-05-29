#include "GameWindow.hpp"

QTeam::QTeam(QWidget * _parent, const Team & _team, 
      QFont _font_num, QFont _font_char) : 
    QWidget(_parent), 
    team(_team), 
    font_num(_font_num), 
    font_char(_font_char) 
{
    qteam_layout = new QVBoxLayout(this);
        qpoints_invested = new QLabel(this);
        qpoints_invested->setAlignment(Qt::AlignCenter);
        qpoints_invested->setFont(font_num);
    qteam_layout->addWidget(qpoints_invested, Qt::AlignCenter);
        qaccount_string = new QLabel(QString("STAN KONTA"));
        qaccount_string->setAlignment(Qt::AlignCenter);
        qaccount_string->setFont(font_char);
    qteam_layout->addWidget(qaccount_string, Qt::AlignCenter);
        qpoints = new QLabel(this);
        qpoints->setFont(font_num);
        qpoints->setAlignment(Qt::AlignCenter);
    qteam_layout->addWidget(qpoints, Qt::AlignCenter);
    qteam_layout->setStretch(0,2);
    qteam_layout->setStretch(1,1);
    qteam_layout->setStretch(2,2);
    refresh();
}

void QTeam::refresh() {
    qpoints_invested->setText(QString::number(team.get_points_invested()));
    qpoints->setText(QString::number(team.get_points()));
    if (team.ishighlighted()) {
        qpoints_invested->setStyleSheet("QLabel { background-color : "+ QString::fromStdString(team.get_hcolor()) +"; color : white; }");
        qaccount_string->setStyleSheet("QLabel { background-color : black; color : " + QString::fromStdString(team.get_hcolor()) +"; }");
        qpoints->setStyleSheet("QLabel { background-color : " + QString::fromStdString(team.get_hcolor()) + "; color : white; }");
    } else {
        qpoints_invested->setStyleSheet("QLabel { background-color : "+ QString::fromStdString(team.get_color()) +"; color : white; }");
        qaccount_string->setStyleSheet("QLabel { background-color : black; color : " + QString::fromStdString(team.get_color()) +"; }");
        qpoints->setStyleSheet("QLabel { background-color : " + QString::fromStdString(team.get_color()) + "; color : white; }");
    }
    qpoints_invested->update();
    qaccount_string->update();
    qpoints->update();
}

QAnswerProps::QAnswerProps(QWidget * _parent, QFont _font_char) : 
    QWidget(_parent), 
    font_char(_font_char) 
{
    for (int i=0;i<4;++i) {
        qtips[i] = new QLabel(this);
    }
    lay = new QGridLayout(this);
    for (auto & x : qtips) {
        x->setAlignment(Qt::AlignCenter);
        x->setStyleSheet("QLabel {background-color : black; color : white; }");
        x->setFont(font_char);
    }
    lay->addWidget(qtips[0],0,0);
    lay->addWidget(qtips[1],0,1);
    lay->addWidget(qtips[2],1,0);
    lay->addWidget(qtips[3],1,1);
}
void QAnswerProps::refresh(bool is_visible, std::array<std::string,4> tips) {
    if (!is_visible) {
        for (auto & x : qtips) {
            x->clear();
        }
    } else {
        for (int i=0;i<4;++i) {
            qtips[i]->setText(QString::fromStdString(tips[i]));
        }
    }
}

MyQTimeLabel::MyQTimeLabel(QWidget* parent, const GEngine & _gengine) : 
    QLabel(parent), 
    gengine(_gengine) 
{}

void MyQTimeLabel::time_refresh() {
    this->setText(QString::number(gengine.get_time_left()));
    this->update();
}

GameWindow::GameWindow(const GEngine & _gengine) : gengine(_gengine) {
    QFontDatabase::addApplicationFont("./font/01 Digit.ttf");
    QFont font("01 Digit",120);
    QFont font2("Arial",50);
    QFont font3("01 Digit",50);

    this->setWindowTitle("Awantura o Kasę");
    this->setStyleSheet("QWidget { background-color : black;}");
    qmain_layout = new QVBoxLayout(this);
        qlic_layout = new QHBoxLayout();
            qlic = new QLabel(QString("LICYTACJA"),this);
            qlic->setAlignment(Qt::AlignCenter);
            qlic->setStyleSheet("QLabel { background-color : black; color : white; }");
            qlic->setFont(font2);
        qlic_layout->addWidget(qlic);
            qtimestr = new QLabel(QString("CZAS"),this);
            qtimestr->setFont(font2);
            qtimestr->setStyleSheet("QLabel { background-color : black; color : white; }");
            qtimestr->setAlignment(Qt::AlignCenter);
        qlic_layout->addWidget(qtimestr);
        qlic_layout->setStretch(0, 3);
        qlic_layout->setStretch(1, 1);
    qmain_layout->addLayout(qlic_layout);
        qteams_layout = new QHBoxLayout();
            qteam1 = new QTeam(this,gengine.get_team(0),font,font2);
        qteams_layout->addWidget(qteam1);
            qteam2 = new QTeam(this,gengine.get_team(1),font,font2);
        qteams_layout->addWidget(qteam2);
            qteam3 = new QTeam(this,gengine.get_team(2),font,font2);
        qteams_layout->addWidget(qteam3);
            qpot_layout = new QVBoxLayout();
                qtimer = new MyQTimeLabel(this,gengine);
                qtimer->setStyleSheet("QLabel {background-color : black; color : white; }");
                qtimer->setFont(font);
                qtimer->setAlignment(Qt::AlignCenter);
                qtimer->setText(QString::number(gengine.get_time_left()));
                qtimer->update();
                    gwtimer = new QTimer(this);
                    gwtimer->setInterval(1000);
                    gwtimer->start();
                QObject::connect(gwtimer,&QTimer::timeout,
                                 qtimer,&MyQTimeLabel::time_refresh);
            qpot_layout->addWidget(qtimer);
                qpot_str = new QLabel(QString("PULA"),this);
                qpot_str->setStyleSheet("QLabel {background-color : black; color : white; }");
                qpot_str->setFont(font2);
                qpot_str->setAlignment(Qt::AlignCenter);
            qpot_layout->addWidget(qpot_str);
                qpot = new QLabel(this);
                qpot->setStyleSheet("QLabel {background-color : black; color : white; }");
                qpot->setFont(font);
                qpot->setAlignment(Qt::AlignCenter);
            qpot_layout->addWidget(qpot);
            qpot_layout->setStretch(0,2);
            qpot_layout->setStretch(1,1);
            qpot_layout->setStretch(2,2);
        qteams_layout->addLayout(qpot_layout);
        qteams_layout->setStretch(0,1);
        qteams_layout->setStretch(1,1);
        qteams_layout->setStretch(2,1);
        qteams_layout->setStretch(3,1);
    qmain_layout->addLayout(qteams_layout);
        qcategory = new QLabel(this);
        qcategory->setStyleSheet("QLabel {background-color : black; color : white; }");
        qcategory->setFont(font2);
        qcategory->setAlignment(Qt::AlignCenter);
    qmain_layout->addWidget(qcategory);
        qquestion = new QLabel(this);
        qquestion->setStyleSheet("QLabel {background-color : black; color : white; }");
        qquestion->setWordWrap(true);
        qquestion->setFont(font2);
        qquestion->setAlignment(Qt::AlignCenter);
    qmain_layout->addWidget(qquestion);
        qanstip = new QAnswerProps(this,font2);
    qmain_layout->addWidget(qanstip);
        qquestnr = new QLabel(this);
        qquestnr->setAlignment(Qt::AlignRight);
        qquestnr->setStyleSheet("QLabel { background-color : black; color : white; }");
        qquestnr->setFont(QFont("Arial",8)); 
    qmain_layout->addWidget(qquestnr);
    qmain_layout->setStretch(0,1);
    qmain_layout->setStretch(1,5);
    qmain_layout->setStretch(2,1);
    qmain_layout->setStretch(3,3.8);
    qmain_layout->setStretch(4,0.2);

    for (auto & x : gengine.get_all_categories()) {
        categories.push_back(QString::fromStdString(x));
    }
    refresh();
}
void GameWindow::refresh() {
    qteam1->refresh();
    qteam2->refresh();
    qteam3->refresh();
    qpot->setText(QString::number(gengine.get_pot()));
    qpot->update();
    if (gengine.is_category_visible()) {
        qcategory->setText(QString::fromStdString(gengine.get_current_question().get_category()));
    } else {
        qcategory->clear();
    }
    qcategory->update();
    if (gengine.is_question_visible()) {
        qquestion->setText(QString::fromStdString(gengine.get_current_question().get_question()));
        qquestnr->setText(QString::number(gengine.get_current_question().get_id()));
    } else {
        qquestion->clear();
        qquestnr->clear();
    }
    qquestion->update();
    qquestnr->update();
    qanstip->refresh(gengine.is_tips_visible(),gengine.get_tips());
}

void GameWindow::cat_rand_animation() {
    int j = gengine.get_current_question().get_id();
    for (int i = j-33; i<j;++i) {
        qcategory->setText(categories[i%categories.size()]);
        qcategory->repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
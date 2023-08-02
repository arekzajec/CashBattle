#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include "GEngine.hpp"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFontDatabase>
#include <QTimer>
#include <vector>
#include <random>

class QTeamLocInterface {
    public:
    virtual QString strAccount() = 0;
};

class QTeamLocPL : public QTeamLocInterface {
    public:
    QString strAccount() {return "STAN KONTA";}
};

class QTeamLocEN : public QTeamLocInterface {
    public:
    QString strAccount() {return "ACCOUNT";}
};


class GameWindowLocInterface {
    protected:
    QTeamLocInterface * qteam;
    public:
    virtual QString strTitle() = 0;
    virtual QString strLicitation() = 0;
    virtual QString strTime() = 0;
    virtual QString strPot() = 0;
    QTeamLocInterface * getQTeamLoc() {return qteam;}
};

class GameWindowLocPL : public GameWindowLocInterface {
    public:
    GameWindowLocPL() {qteam = new QTeamLocPL;}
    QString strTitle() {return "Awantura o Kasę";}
    QString strLicitation() {return "LICYTACJA";}
    QString strTime() {return "CZAS";}
    QString strPot() {return "PULA";}
};

class GameWindowLocEN : public GameWindowLocInterface {
    public:
    GameWindowLocEN() {qteam = new QTeamLocEN;}
    QString strTitle() {return "Cash Battle";}
    QString strLicitation() {return "LICITATION";}
    QString strTime() {return "TIME";}
    QString strPot() {return "POT";}
};

class QTeam : public QWidget {
    const Team & team;
    QVBoxLayout *qteam_layout;
        QLabel *qpoints_invested;
        QLabel *qaccount_string;
        QLabel *qpoints;
    QFont font_num;
    QFont font_char;
public:
    QTeam(QWidget * _parent, QTeamLocInterface * loc, const Team & _team, 
          QFont _font_num, QFont _font_char);
    void refresh();
};

class QAnswerProps : public QWidget {
    std::array<QLabel*,4> qtips;
    QFont font_char;
    QGridLayout * lay;
public:
    QAnswerProps(QWidget * _parent, QFont _font_char);
    void refresh(bool is_visible, std::array<std::string,4> tips);
};

class MyQTimeLabel : public QLabel {
    Q_OBJECT
private:
    const GEngine & gengine;
public slots:
    void time_refresh();
public:
    MyQTimeLabel(QWidget* parent, const GEngine & _gengine);
};

class GameWindow : public QWidget {
    GameWindowLocInterface * loc;
    const GEngine & gengine;
    std::vector<QString> categories;
    bool is_question_nr_visible;

    QVBoxLayout *qmain_layout;
        QHBoxLayout *qlic_layout;
            QLabel *qlic;
            QLabel *qtimestr;
        QHBoxLayout *qteams_layout;
            std::array<QTeam *,3> qteam;
            QVBoxLayout *qpot_layout;
                MyQTimeLabel *qtimer;
                QLabel *qpot_str;
                QLabel *qpot;
        QLabel *qcategory;
        QLabel *qquestion;
        QAnswerProps *qanstip;
        QLabel *qquestnr;

    QTimer *gwtimer;
public:
    GameWindow(GameWindowLocInterface * localization, const GEngine & _gengine, double scale = 1, bool is_mirrored = false, bool _is_question_nr_visible = false);
    void refresh();
    void cat_rand_animation();
};

#endif
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

class QTeam : public QWidget {
    const Team & team;
    QVBoxLayout *qteam_layout;
        QLabel *qpoints_invested;
        QLabel *qaccount_string;
        QLabel *qpoints;
    QFont font_num;
    QFont font_char;
public:
    QTeam(QWidget * _parent, const Team & _team, 
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
    const GEngine & gengine;
    std::vector<QString> categories;

    QVBoxLayout *qmain_layout;
        QHBoxLayout *qlic_layout;
            QLabel *qlic;
            QLabel *qtimestr;
        QHBoxLayout *qteams_layout;
            QTeam *qteam1;
            QTeam *qteam2;
            QTeam *qteam3;
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
    GameWindow(const GEngine & _gengine, double scale = 1);
    void refresh();
    void cat_rand_animation();
};

#endif
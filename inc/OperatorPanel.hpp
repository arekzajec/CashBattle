#ifndef OPERATORPANEL_HPP
#define OPERATORPANEL_HPP

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include "GameWindow.hpp"
#include "GEngine.hpp"
#include <iostream>
#include <algorithm>
#include <QPushButton>
#include <QCommonStyle>
#include <QStyleOptionButton>

class QStatePanel : public QWidget {
    QVBoxLayout * mainlayout;
    std::vector<QLabel *> qstates;
    QLabel * newQLabel(QString str, QFont font);
public:
      QStatePanel(QWidget * parent, QFont font);
      void refresh(state current_state, bool is_any_team_va_banque);
};

class QButtonDesc : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout * mainlayout;
    QPushButton * qbutton;
    QLabel * qdesc;
public:
    QButtonDesc(QWidget * parent, QFont font);
    QButtonDesc(QWidget * parent, QFont font, QString str);
    QButtonDesc(QWidget * parent, QFont font, QIcon ico);
    void setButtonEnabled(bool is_enabled) {qbutton->setEnabled(is_enabled);}
    void refresh();
    void setLabelText(QString str) {qdesc->setText(str);}
signals:
    void released_signal();
};

class QButtonDescGroup : public QWidget {
    Q_OBJECT
private:
    GEngine * gengine;
    QVBoxLayout * mainlayout;
    QLabel * qdesc;
    std::vector<QButtonDesc *> qbuttons;
    void setAllButtonsDisabled() {for(auto & x : qbuttons) x->setButtonEnabled(false);}
    void setButtonsEnabled(const std::initializer_list<int> & args);
    void resetAllLabelText() {for(auto & x: qbuttons) x->setLabelText(QString(""));}
    void setLabelText(int ind,QString str);
    void licitation_disp(Team * ateam);
public:
    QButtonDescGroup(QWidget * parent, GEngine * _gengine, QFont font);
    void refresh();
signals:
    void released_signal(ekey key);
private slots:
    void released_slot();
};

class OperatorPanel : public QWidget {
    Q_OBJECT
private:
    GameWindow * gwindow;
    GEngine * gengine;
    QHBoxLayout * mainlayout;
    QStatePanel * qstatepanel;
    QButtonDescGroup * qbuttons;
    void send2engine_and_refresh(ekey key);
public:
    OperatorPanel(GameWindow * _gwindow, GEngine * _gengine);
    void refresh();
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void qbuttonhandler(ekey key);

};








#endif
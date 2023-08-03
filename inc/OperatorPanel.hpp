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
#include <qboxlayout.h>
#include <qlabel.h>

class QStatePanelLocInterface {
    public:
    virtual QString strState() = 0;
    virtual QString strDeactivated() = 0;
    virtual QString strPunishment() = 0;
    virtual QString strCategory() = 0;
    virtual QString strExtraPot() = 0;
    virtual QString strTip() = 0;
    virtual QString strLicitationStart() = 0;
    virtual QString strLicitation() = 0;
    virtual QString strLicitationBlock() = 0;
    virtual QString strSold() = 0;
    virtual QString strMusical() = 0;
    virtual QString strQuestion() = 0;
    virtual QString strEnd() = 0;
};

class QStatePanelLocPL : public QStatePanelLocInterface {
    public:
    QString strState() {return "Stan";} 
    QString strDeactivated() {return "nieaktywny";}
    QString strPunishment() {return "kara";}
    QString strCategory() {return "kategoria";}
    QString strExtraPot() {return "ekstra pula";}
    QString strTip() {return "podpowiedź";}
    QString strLicitationStart() {return "licytacja - start";}
    QString strLicitation() {return "licytacja";}
    QString strLicitationBlock() {return "licytacja - blokada";}
    QString strSold() {return "sprzedane";}
    QString strMusical() {return "odtwarzanie";}
    QString strQuestion() {return "pytanie";}
    QString strEnd() {return "koniec";}
};

class QStatePanelLocEN : public QStatePanelLocInterface {
    QString strState() {return "State";} 
    QString strDeactivated() {return "deactivated";}
    QString strPunishment() {return "punishment";}
    QString strCategory() {return "category";}
    QString strExtraPot() {return "extra pool";}
    QString strTip() {return "hint";}
    QString strLicitationStart() {return "bidding - start";}
    QString strLicitation() {return "bidding";}
    QString strLicitationBlock() {return "bidding - blocked";}
    QString strSold() {return "sold";}
    QString strMusical() {return "play music";}
    QString strQuestion() {return "question";}
    QString strEnd() {return "end";}
};

class QButtonDescGroupLocInterface {
    protected:
    QStatePanelLocInterface * qstate;
    public:
    QButtonDescGroupLocInterface(QStatePanelLocInterface * q) : qstate(q) {}
    QStatePanelLocInterface * getQStateLoc() {return qstate;}
    virtual QString strGoTo() = 0;
    virtual QString strUp100Team() = 0;
    virtual QString strDown100Team() = 0;
    virtual QString strPickTeam() = 0;
    virtual QString strUp100Pot() = 0;
    virtual QString strDown100Pot() = 0;
    virtual QString strUp100TeamLic() = 0;
    virtual QString strDown100TeamLic() = 0;
    virtual QString strCorrectAnswer() = 0;
    virtual QString strIncorrectAnswer() = 0;
    virtual QString strShowTip() = 0;
    virtual QString strStopTime() = 0;
    virtual QString strStartTime() = 0;
    virtual QString strUndo() = 0;
    virtual QString strLeads() = 0;
    virtual QString strVaBanque() = 0;
    virtual QString strBlocks() = 0;
    virtual QString strForceTip() = 0;
    virtual QString strForceBB() = 0;
};

class QButtonDescGroupLocPL : public QButtonDescGroupLocInterface {
    public:
    QButtonDescGroupLocPL() : QButtonDescGroupLocInterface(new QStatePanelLocPL) {}
    QButtonDescGroupLocPL(QStatePanelLocInterface * q) : QButtonDescGroupLocInterface(q) {}
    QString strGoTo() {return "przejdź do: ";}
    QString strUp100Team() {return "zwróc 100 drużynie: ";}
    QString strDown100Team() {return "odbierz 100 drużynie: ";}
    QString strPickTeam() {return "wybierz drużynę: ";}
    QString strUp100Pot() {return "dodaj 100 do puli";}
    QString strDown100Pot() {return "zabierz 100 z puli";}
    QString strUp100TeamLic() {return "zwiększ o 100 kwotę drużyny: ";}
    QString strDown100TeamLic() {return "zmniejsz o 100 kwotę drużyny: ";}
    QString strCorrectAnswer() {return "odpowiedź poprawna";}
    QString strIncorrectAnswer() {return "odpowiedź błędna";}
    QString strShowTip() {return "pokaż podpowiedź";}
    QString strStopTime() {return "stop czas odpowiedzi";}
    QString strStartTime() {return "start czas odpowiedzi";}
    QString strUndo() {return "cofnij";}
    QString strLeads() {return " licytują!";}
    QString strVaBanque() {return " va banque!";}
    QString strBlocks() {return " blokują przeciwników!";}
    QString strForceTip() {return "wymuś podpowiedź";}
    QString strForceBB() {return "wymuś czarną skrzynkę";}
};

class QButtonDescGroupLocEN : public QButtonDescGroupLocInterface {
    public:
    QButtonDescGroupLocEN() : QButtonDescGroupLocInterface(new QStatePanelLocEN) {}
    QButtonDescGroupLocEN(QStatePanelLocInterface * q) : QButtonDescGroupLocInterface(q) {}
    QString strGoTo() {return "go to: ";}
    QString strUp100Team() {return "return 100 to team: ";}
    QString strDown100Team() {return "take 100 from team: ";}
    QString strPickTeam() {return "pick team: ";}
    QString strUp100Pot() {return "add 100 to pool";}
    QString strDown100Pot() {return "take 100 from pool";}
    QString strUp100TeamLic() {return "add 100 to bid of team: ";}
    QString strDown100TeamLic() {return "take 100 from bid of team: ";}
    QString strCorrectAnswer() {return "correct answer";}
    QString strIncorrectAnswer() {return "incorrect answer";}
    QString strShowTip() {return "show hint";}
    QString strStopTime() {return "stop reply time";}
    QString strStartTime() {return "start reply time";}
    QString strUndo() {return "undo";}
    QString strLeads() {return " team is leading!";}
    QString strVaBanque() {return " va banque!";}
    QString strBlocks() {return " blocks oponents!";}
    QString strForceTip() {return "force hint";}
    QString strForceBB() {return "force black box";}
};

class OperatorQuestionInfoLocInterface {
    public:
    virtual QString strMusical() = 0;
    virtual QString strRegular() = 0;
};

class OperatorQuestionInfoLocPL : public OperatorQuestionInfoLocInterface {
    public:
    QString strMusical() {return "Pytanie muzyczne";}
    QString strRegular() {return "Pytanie zwykłe";}
};

class OperatorQuestionInfoLocEN : public OperatorQuestionInfoLocInterface {
    public:
    QString strMusical() {return "Musical question";}
    QString strRegular() {return "Regular question";}
};


class OperatorPanelLocInterface {
    protected:
    QStatePanelLocInterface * qstate;
    QButtonDescGroupLocInterface * qbutton;
    GameWindowLocInterface * gwindow;
    OperatorQuestionInfoLocInterface * questinf;
    public:
    QStatePanelLocInterface * getQStateLoc() {return qstate;}
    QButtonDescGroupLocInterface * getQButtonLoc() {return qbutton;}
    GameWindowLocInterface * getGameWinLoc() {return gwindow;}
    OperatorQuestionInfoLocInterface * getOperQInfLoc() {return questinf;}
};

class OperatorPanelLocPL : public OperatorPanelLocInterface {
    public:
    OperatorPanelLocPL() {
        qstate = new QStatePanelLocPL;
        qbutton = new QButtonDescGroupLocPL(qstate);
        gwindow = new GameWindowLocPL;
        questinf = new OperatorQuestionInfoLocPL;
    }
};

class OperatorPanelLocEN : public OperatorPanelLocInterface {
    public:
    OperatorPanelLocEN() {
        qstate = new QStatePanelLocEN;
        qbutton = new QButtonDescGroupLocEN(qstate);
        gwindow = new GameWindowLocEN;
        questinf = new OperatorQuestionInfoLocEN;
    }
};


class QStatePanel : public QWidget {
    QVBoxLayout * mainlayout;
    std::vector<QLabel *> qstates;
    QLabel * newQLabel(QString str, QFont font);
public:
      QStatePanel(QWidget * parent, QStatePanelLocInterface * loc, QFont font);
      void refresh(state current_state, bool is_any_team_va_banque);
};

class QButtonDesc : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout * mainlayout;
    QPushButton * qbutton;
    QLabel * qdesc;
public:
    QButtonDesc(QWidget * parent, QFont font, double scale=1.0);
    QButtonDesc(QWidget * parent, QFont font, QString str, double scale=1.0);
    QButtonDesc(QWidget * parent, QFont font, QIcon ico, double scale=1.0);
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
    QButtonDescGroupLocInterface * loc;
    QVBoxLayout * mainlayout;
    QLabel * qdesc;
    std::vector<QButtonDesc *> qbuttons;
    void setAllButtonsDisabled() {for(auto & x : qbuttons) x->setButtonEnabled(false);}
    void setButtonsEnabled(const std::initializer_list<int> & args);
    void resetAllLabelText() {for(auto & x: qbuttons) x->setLabelText(QString(""));}
    void setLabelText(int ind,QString str);
    void licitation_disp(Team * ateam);
public:
    QButtonDescGroup(QWidget * parent,QButtonDescGroupLocInterface * localization, GEngine * _gengine, QFont font, double scale=1.0);
    void refresh();
signals:
    void released_signal(ekey key);
private slots:
    void released_slot();
};

class OperatorQuestionInfo : public QWidget {
    Q_OBJECT
private:
    GEngine * gengine;
    OperatorQuestionInfoLocInterface * loc;
    QVBoxLayout *layout;
    QHBoxLayout *flay;
    QLabel *ismusic;
    QLabel *qquestion_nr;
    QLabel *qquestion;
    QLabel *qanswer;
    QLabel *qtip1;
    QLabel *qtip2;
    QLabel *qtip3;
public:
    OperatorQuestionInfo(QWidget * parent, OperatorQuestionInfoLocInterface * localization, GEngine * _gengine, QFont font);
    void replace_question(const Question & q);
    void clear();
};

class OperatorPanel : public QWidget {
    Q_OBJECT
private:
    OperatorPanelLocInterface * loc;
    GameWindow * gwindow;
    GEngine * gengine;
    GameWindow * qlocalgamew;
    OperatorQuestionInfo * qquest;
    QHBoxLayout * mainlayout;
    QStatePanel * qstatepanel;
    QButtonDescGroup * qbuttons;
    QVBoxLayout * rightlayout;
    void send2engine_and_refresh(ekey key);
public:
    OperatorPanel(OperatorPanelLocInterface * localization, GameWindow * _gwindow, GEngine * _gengine, double scale = 1.0);
    void refresh();
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void qbuttonhandler(ekey key);

};








#endif
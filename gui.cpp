#include "gui.h"


Gui::Gui(QPoint pos, QSize size,QWidget* parent) :QWidget(parent)
{



    mainLayout = new QVBoxLayout();
    menu = new QHBoxLayout();
    statContainer = new QVBoxLayout();
    statContainer2 = new QVBoxLayout();

    reset = new QPushButton();
    reset->setText("Reset");

    oneStep = new QPushButton();
    oneStep->setText("1 Step");

    run = new QPushButton("Run");

    menu->addWidget(reset);
    menu->addWidget(oneStep);
    menu->addWidget(run);

    //Definition du widget stat


    Step = new QLabel(QString("Step : 0"));
    currentState = new QLabel(QString("currentState : 1"));
    cursorPosition = new QLabel(QString("cursorPosition : (0;0)"));

    statContainer->addWidget(Step);
    statContainer->addWidget(currentState);
    statContainer2->addWidget(cursorPosition);

    //Ajout du tableau de stat au menu
    menu->addLayout(statContainer);
    menu->addLayout(statContainer2);

    mainLayout->addLayout(menu);
    setLayout(mainLayout);

   // move(pos);
    setMaximumSize(size);


}

void Gui::updateStep(int scr){
    QString tmpS("Step : ");
    tmpS += QString::number(scr);
    Step->setText(tmpS);
}

void Gui::updateCurrentState(int scr){
    QString tmpS("currentState : ");
    tmpS += QString::number(scr);
    currentState->setText(tmpS);
}

void Gui::updateCursorPos(int x, int y){
    QString tmpS("Position : (");
    tmpS += QString::number(x) + QString(" ; ") + QString::number(y)+QString(")");
    cursorPosition->setText(tmpS);
}

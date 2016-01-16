#ifndef QSFCANVAS_H
#define QSFCANVAS_H
#include <iostream>
#include <sstream>
#include <QEvent>
#include <QKeyEvent>
#include <boost/random.hpp>
#include "qsfml.h"
#include "displaymanager.h"
#include "time.h"

class QSFcanvas : public Qsfml
{

    Q_OBJECT

public:
    QSFcanvas(const QPoint& Position, const QSize& Size,QWidget *parent = 0);

signals:
    void sendStep(int);
    void sendCurrentState(int);
    void sendCursorPos(int,int);
    void runChange();

public slots:
    void reset();
    void stepbystep();
    void run();


private:
    World world;
    DisplayManager display;
    int step;
    sf::Clock Time;
    bool keepGoing = false;
    int currentState = 1;
    const int nbrStates = (sizeX-2)*(sizeY-2)+1;

    bool leftClickPressed = false;

    boost::random::mt19937 random;


    void pause();

    void OnInit();
    void OnUpdate();
    void keyReleaseEvent(QKeyEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
};

#endif // QSFCANVAS_H

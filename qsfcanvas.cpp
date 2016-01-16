#include "qsfcanvas.h"


QSFcanvas::QSFcanvas(const QPoint& Position, const QSize& Size, QWidget* parent) : Qsfml(parent, Position, Size)
{
    step =0;
    setMouseTracking(true);
    random.seed(time(NULL));
}







void QSFcanvas::keyReleaseEvent(QKeyEvent * e){
    if(e->key() == Qt::Key_Space){
        run();
    }
    else if(e->key() == Qt::Key_Right){
        stepbystep();
    }

}

void QSFcanvas::mouseMoveEvent(QMouseEvent * event){
    emit sendCursorPos(event->pos().x()/(GetWidth()/sizeX),event->pos().y()/(GetHeight()/sizeY));
    if(leftClickPressed){
        QPair<int,int> pair(event->pos().x()/(GetWidth()/sizeX),event->pos().y()/(GetHeight()/sizeY));
        Automaton automa(world.getAutomata().value(pair));
        automa.setState(0,currentState);
        world.getAutomata().insert(pair,automa);
    }
}

void QSFcanvas::mousePressEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton)
        leftClickPressed = true;
}

void QSFcanvas::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton){
        QPair<int,int> pair(event->pos().x()/(GetWidth()/sizeX),event->pos().y()/(GetHeight()/sizeY));
        Automaton automa(world.getAutomata().value(pair));
        automa.setState(0,currentState);
        world.getAutomata().insert(pair,automa);
       leftClickPressed = false;

    }
}
void QSFcanvas::wheelEvent(QWheelEvent * event){
    if(event->delta() > 0)
        currentState++;


    currentState%=nbrStates;

    emit sendCurrentState(currentState);
    std::cout << "etat courant :" << currentState << std::endl;

}

void QSFcanvas::OnInit(){

    boost::random::uniform_int_distribution<> rd(1,(sizeX-2)*(sizeY-2));

    QVector<QPair<int,int> > N;
    N.append(QPair<int,int>(-1,0));
    N.append(QPair<int,int>(1,0));
    N.append(QPair<int,int>(0,-1));
    N.append(QPair<int,int>(0,1));
//    N.append(QPair<int,int>(-1,1));
//    N.append(QPair<int,int>(1,1));
//    N.append(QPair<int,int>(1,-1));
//    N.append(QPair<int,int>(-1,-1));

    QVector<int>** initS = new QVector<int>*[sizeX];


    int dir = 2;

    for(int i = 0; i <sizeX; i++){
        initS[i] = new  QVector<int>[sizeY];
        for(int j = 0; j < sizeY; j++){
            initS[i][j] = QVector<int>(3);
            initS[i][j].replace(0,0);
            initS[i][j].replace(1,dir);
            initS[i][j].replace(2,0);

            dir=(dir+1)%2+2;


        }
    }

    QVector<int> states;
    for(int i = 1 ; i < nbrStates; i++)
        states.append(i);

    for(int i = 1; i <sizeX-1; i++){
        for(int j = 1; j < sizeY-1; j++){
            int r = rd(random);
            initS[i][j].replace(0,states[r]);

            states.remove(r);
            states.squeeze();
            if(states.size() > 0)
                rd = boost::random::uniform_int_distribution<>(0,states.size()-1);

        }
    }

//    initS[50][50] = 1;

    world = World(sizeX,sizeY,N,initS);

    display = DisplayManager(GetWidth(),GetHeight(),nbrStates,sizeX,sizeY);
   // display.updateCells(world.getAutomata());
    std::cout << display.automataToString(world.getAutomata()).toStdString() << std::endl;


}



void QSFcanvas::reset(){

    step = 0;
    world.reset();
    emit sendStep(step);
}

void QSFcanvas::stepbystep(){

    step++;
    world.nextStep();
    emit sendStep(step);
    std::cout << display.automataToString(world.getAutomata()).toStdString() << std::endl;
}

void QSFcanvas::run(){
    keepGoing = !keepGoing;
    emit runChange();
}

void QSFcanvas::pause(){
    if(myTimer.isActive())
        myTimer.stop();
    else myTimer.start();
}


void QSFcanvas::OnUpdate()
{
    //display.updateCells(world.getAutomata());
  //  std::cout << step << std::endl;
    display.updateCells(world.getAutomata());

    Clear();
    display.draw(*this);
    if(keepGoing){


        stepbystep();
    }


}

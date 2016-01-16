#ifndef AUTOMATON_H
#define AUTOMATON_H
#include <QVector>
#include <QPair>

class Automaton
{
public:
    Automaton(){}
    Automaton(QVector<QPair<int,int>> N,QVector<int> S);
    Automaton(const Automaton& a)
        : neighborhood(a.neighborhood)
        , state(a.state){}

    QVector<QPair<int,int> >& getNeighbors();

    int getState(int i);
    void setState(int,int);



private:
    QVector<QPair<int,int> > neighborhood;
    QVector<int> state;


};

#endif // AUTOMATON_H

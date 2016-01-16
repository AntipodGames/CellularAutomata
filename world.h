#ifndef WORLD_H
#define WORLD_H
#include <QMap>
#include "automaton.h"
#include <time.h>
#include <iostream>
#include "boost/random.hpp"
#define  ANT_SEARCH 1
#define  BASE 2
#define  FOOD 3
#define  ANT_SEARCH2 4
#define  ANT_SEARCH3 5
#define  ANT_RETURN 6
#define  PHERO_SEARCH 7
#define  PHERO_SEARCH2 8
#define  PHERO_RETURN 9
#define  BASE_EMPTY 10
#define  BASE_EXPEND 11
#define  IN_BASE 12

class World
{

public:


    World(){}

    World(QPair<int,int>, QVector<QPair<int, int> > N, QVector<int> **);
    World(int, int, QVector<QPair<int, int> > N, QVector<int> **);

    void nextStep();
    void reset();

    QPair<int,int> neighboorCoord(Automaton, int, QPair<int, int>);

    Automaton getAutomaton(int,int);
    QMap<QPair<int,int>,Automaton>& getAutomata();

private:
    QPair<int,int> size;
    QMap<QPair<int,int>,Automaton> automata;

    void transitionFunction(QMap<QPair<int,int>,Automaton>&, QPair<int, int> coord);
    boost::random::mt19937 random;
    int nbrofAnt=0;
    int nbrofDead = 0;
    int nbrofPhero = 0;

};

#endif // WORLD_H

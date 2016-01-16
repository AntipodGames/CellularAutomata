#include "automaton.h"


Automaton::Automaton(QVector<QPair<int, int> > N, QVector<int> S){
    neighborhood = N;
    state = S;
}


QVector<QPair<int,int> >& Automaton::getNeighbors(){
    return neighborhood;
}


int Automaton::getState(int i){
    return state[i];
}

void Automaton::setState(int i, int s){
    state.replace(i,s);
}


#include "world.h"

World::World(QPair<int, int> s,QVector<QPair<int,int>> N,QVector<int>** initStates){
    size = s;


    for(int x = 0; x < size.second;x++){
        for(int y = 0; y < size.first; y++){
            automata.insert(QPair<int,int>(x,y),Automaton(N,initStates[x][y]));
        }
    }

}

World::World(int w, int h, QVector<QPair<int, int> > N,QVector<int>** initStates){

    size = QPair<int,int>(w,h);
    for(int x = 0; x < size.second;x++){
        for(int y = 0; y < size.first; y++){
            automata.insert(QPair<int,int>(x,y),Automaton(N,initStates[x][y]));
        }
    }
}

void World::nextStep(){

    QMap<QPair<int,int>,Automaton> newAutomata/*(automata)*/;

    nbrofAnt = 0;
    nbrofDead = 0;
    nbrofPhero = 0;
    for(auto a = automata.begin(); a != automata.end();a++){
        Automaton tmpA = a.value();
        if(!newAutomata.contains(a.key())){

            if(tmpA.getState(0) != 0){
                transitionFunction(newAutomata,a.key());
                //newAutomata.insert(a.key(),at);
            }
            else newAutomata.insert(a.key(),a.value());



        }

    }



    automata = newAutomata;

}

void World::reset(){
    for(auto i = automata.begin(); i != automata.end();i++){
        Automaton tmp(i.value());
        tmp.setState(0,0);
        automata.insert(i.key(),tmp);
    }
}

Automaton World::getAutomaton(int x, int y){
    QPair<int,int> coord(x,y);

    return automata.value(coord);
}

QMap<QPair<int,int>,Automaton>& World::getAutomata(){
    return automata;
}

QPair<int,int> World::neighboorCoord(Automaton current, int i,QPair<int,int> coord){
    int x = current.getNeighbors()[i].first+coord.first;
    int y = current.getNeighbors()[i].second+coord.second;
    if(x > size.first-1)
        x = 0;
    else if(x < 0)
        x = size.first-1;

    if(y> size.second-1)
        y = 0;
    else if(y < 0)
        y = size.second-1;
    QPair<int,int> nCoord(x,y);
    return nCoord;
}

void World::transitionFunction(QMap<QPair<int, int>, Automaton> & newAuto, QPair<int,int> coord){

    Automaton current(automata.value(coord));

    QPair<int,int> nCoord;
    Automaton tmp;
    Automaton tmp2;

    if(current.getState(2) == 0){
        nCoord = neighboorCoord(current,0,coord);
        tmp = automata.value(nCoord);
        nCoord = neighboorCoord(current,2,coord);
        tmp2 = automata.value(nCoord);
        if(tmp.getState(0) == 0 && tmp2.getState(0) == 0)
            current.setState(2,1);
        else if (tmp.getState(2) != 0 || tmp2.getState(2) != 0 )
            current.setState(2,(tmp.getState(2) +tmp2.getState(2)+1));

    }else {


        if(current.getState(1) == 0){
            nCoord = neighboorCoord(current,current.getState(1),coord);

            tmp = automata.value(nCoord);

            if(tmp.getState(1) == current.getState(1)+1
                    && tmp.getState(2) != 0 ){

                current.setState(0,tmp.getState(0));
                current.setState(1,tmp.getState(1));

            }
        }else if(current.getState(1) == 1){
            nCoord = neighboorCoord(current,current.getState(1),coord);

            tmp = automata.value(nCoord);


            if(tmp.getState(1) == current.getState(1)-1
                    && tmp.getState(2) != 0){
                current.setState(0,tmp.getState(0));
                current.setState(1,tmp.getState(1));

            }
        }else if(current.getState(1) == 2){
            nCoord = neighboorCoord(current,current.getState(1),coord);

            tmp = automata.value(nCoord);


            if(tmp.getState(1) == current.getState(1)+1
                    && tmp.getState(2) != 0){
                current.setState(0,tmp.getState(0));
                current.setState(1,tmp.getState(1));
            }
        }else if(current.getState(1) == 3){
            nCoord = neighboorCoord(current,current.getState(1),coord);

            tmp = automata.value(nCoord);

            if(tmp.getState(1) == current.getState(1)-1
                    && tmp.getState(2) != 0){
                current.setState(0,tmp.getState(0));
                current.setState(1,tmp.getState(1));
                //                newDir = tmp.getState(1);
            }

        }




        nCoord = neighboorCoord(current,0,coord);
        tmp = automata.value(nCoord);
        nCoord = neighboorCoord(current,1,coord);
        tmp2 = automata.value(nCoord);
        if( current.getState(0)/current.getState(2) > current.getState(2)
                && tmp.getState(0) != 0){
            current.setState(1,0);
        }else if(current.getState(0)/current.getState(2) <= current.getState(2)
                 && tmp2.getState(0) != 0){
            current.setState(1,1);
        }


        nCoord = neighboorCoord(current,2,coord);
        tmp = automata.value(nCoord);
        nCoord = neighboorCoord(current,3,coord);
        tmp2 = automata.value(nCoord);
        if( current.getState(0)/current.getState(2) > current.getState(2)
                && tmp.getState(0) != 0){
            current.setState(1,2);
        }else if(current.getState(0)/current.getState(2) <= current.getState(2)
                 && tmp2.getState(0) != 0){
            current.setState(1,3);
        }




        nCoord = neighboorCoord(current,0,coord);
        tmp = automata.value(nCoord);
        nCoord = neighboorCoord(current,1,coord);
        tmp2 = automata.value(nCoord);
        if(current.getState(0) > tmp2.getState(0)
                && tmp2.getState(0) != 0){
            current.setState(1,1);
        }else if(current.getState(0) < tmp.getState(0)
                 && tmp.getState(0) != 0){
            current.setState(1,0);
        }


        nCoord = neighboorCoord(current,2,coord);
        tmp = automata.value(nCoord);
        nCoord = neighboorCoord(current,3,coord);
        tmp2 = automata.value(nCoord);
        if(tmp.getState(0) > current.getState(0)&& tmp.getState(0) != 0 )
            current.setState(1,2);
        else if(tmp2.getState(0) < current.getState(0)&& tmp2.getState(0) != 0 )
            current.setState(1,3);


    }

    newAuto.insert(coord,current);


}

#include "displaymanager.h"

DisplayManager::DisplayManager(int WIDTH,int HEIGHT,int nbrStates, int w, int h){



    colors.append(sf::Color::White);
    //    colors.append(sf::Color::Red);
    //    colors.append(sf::Color::Blue);
    //    colors.append(sf::Color::Green);

    rand.seed(420);

    boost::random::uniform_int_distribution<> rd(0,255);
    int r = rd(rand);

    int g = rd(rand);
    int b = rd(rand);

    for(int i = 4; i < nbrStates; i++){
        colors.append(sf::Color(r,g,b));
        r = rd(rand);
        g = rd(rand);
        b = rd(rand);

    }

    for(int x = 0; x <WIDTH ;x+=WIDTH/w){
        for(int y = 0; y < HEIGHT; y+=HEIGHT/h){
            sf::RectangleShape rect(x+WIDTH/w,y+HEIGHT/h); //::Rectangle(x,y,x+WIDTH/w,y+HEIGHT/h,colors[0]);
            rect.setPosition(x,y);
            rect.setFillColor(colors[0]);
            cells.insert(QPair<int,int>(x/(WIDTH/h),y/(HEIGHT/w)),rect);
        }
    }


}

void DisplayManager::updateCells(QMap<QPair<int, int>, Automaton>& automats){
    for(auto i = automats.begin(); i != automats.end();i++){
        Automaton a(i.value());
        sf::RectangleShape shp = cells.value(i.key());

        if(a.getState(0) == 0)
            shp.SetColor(colors[0]);
        else{
            float rgb = ((float)a.getState(0)/(((float)sizeX-2.)*((float)sizeY-2.)))*255.;
            shp.SetColor(sf::Color((int) rgb,(int) rgb,0));
        }
            cells.insert(i.key(),shp);
    }
}

void DisplayManager::draw(sf::RenderWindow & win){
    for(auto i = cells.begin(); i != cells.end(); i++){
        sf::Shape shp = i.value();
        if(shp.GetColor() != sf::Color::White)
            win.Draw(shp);
    }

}

int** DisplayManager::automataToTab(QMap<QPair<int, int>, Automaton> & autos){
    int** tab = new int*[sizeX-1];

    for(int i = 0; i < sizeX-1; i++){
        tab[i] = new int[sizeY-1];
        for(int j = 0; j < sizeY-1; j++){
            QPair<int,int> coord(i+1,j+1);
            Automaton tmp(autos.value(coord));
            tab[i][j] = tmp.getState(0);
        }
    }

    return tab;

}

QString DisplayManager::automataToString(QMap<QPair<int, int>, Automaton> & autos){

    QString result("");

    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            QPair<int,int> coord(j,i);
            Automaton tmp(autos.value(coord));

            result+= " " + QString::number(tmp.getState(0)) + "|" + QString::number(tmp.getState(2));

            if(tmp.getState(1) == 1){

                result+=  " > ";
            }else if(tmp.getState(1) == 0){

                result+= " < ";
            }
            else if(tmp.getState(1) == 2){

                result+= "/\\ ";
            }
            else if(tmp.getState(1) == 3){

                result+= "\\/ ";
            }
        }
        result+= "\n";
    }
    return result;
}



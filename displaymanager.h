#ifndef DISPLAY_H
#define DISPLAY_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <QVector>
#include <QString>
#include "world.h"
#define sizeX 5
#define sizeY 5

class DisplayManager
{
public:
    DisplayManager(){}

    DisplayManager(int,int,int nbrStates,int w, int h);

    void updateCells(QMap<QPair<int, int>, Automaton> &);
    void draw(sf::RenderWindow&);
    int** automataToTab(QMap<QPair<int, int>, Automaton> &);
    QString automataToString(QMap<QPair<int, int>, Automaton> &);

private:
    boost::random::mt19937 rand;

    QVector<sf::Color> colors;
    QMap<QPair<int,int>,sf::RectangleShape> cells;

};

#endif // DISPLAY_H

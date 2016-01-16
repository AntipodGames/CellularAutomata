#include <iostream>
#include <QApplication>
#include "maingui.h"
#define WIDTH 500
#define HEIGHT 550

using namespace std;

int main(int argc, char** argv)
{

    QApplication* App = new QApplication(argc,argv);

    MainGUI* maingui = new MainGUI(WIDTH,HEIGHT);
    maingui->init();
    maingui->show();



    return App->exec();

}


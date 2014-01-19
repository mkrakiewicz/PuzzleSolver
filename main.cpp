#include "puzzlesolverstartscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PuzzleSolverStartScreen w;
    w.show();
    
    return a.exec();
}

#include "puzzlesolverstartscreen.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    PuzzleSolverStartScreen w;
    w.setFixedSize(w.size());
    w.show();

    return a.exec();
}

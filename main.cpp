#include "puzzlesolverstartscreen.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("../lang");
    a.installTranslator(&translator);
    PuzzleSolverStartScreen w;
    w.setFixedSize(w.size());
    w.show();
    
    return a.exec();
}

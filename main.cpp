#include "pswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PSWindow w;
    w.show();
    
    return a.exec();
}

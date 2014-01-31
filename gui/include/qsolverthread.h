#ifndef QSOLVERTHREAD_H
#define QSOLVERTHREAD_H

#include <QThread>
#include "puzzlesolver.h"

class QSolverThread : public QThread, public PuzzleSolver
{
    Q_OBJECT
public:
    explicit QSolverThread(QObject *parent = 0);
    u_int currentOpenStates();
    u_int currentClosedStates();

signals:
    
public slots:
    
};

#endif // QSOLVERTHREAD_H

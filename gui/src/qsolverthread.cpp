#include "qsolverthread.h"

QSolverThread::QSolverThread(QObject *parent) :
    QThread(parent),PuzzleSolver()
{
}

u_int QSolverThread::currentOpenStates()
{
    return stateManager->getOpenStateSize();
}

u_int QSolverThread::currentClosedStates()
{
    return stateManager->getClosedStateSize();
}

#ifndef PUZZLEQOBJECT_H
#define PUZZLEQOBJECT_H
#include <QLabel>


class PuzzleQObject : public QLabel
{
    Q_OBJECT
public:
    explicit PuzzleQObject(QWidget *parent = 0);
    u_int ID;
signals:
    
public slots:
    
};

class QLabelPuzzle : public PuzzleQObject
{
    Q_OBJECT
public:
    explicit QLabelPuzzle(QWidget *parent = 0);
signals:

public slots:

};

#endif // PUZZLEQOBJECT_H

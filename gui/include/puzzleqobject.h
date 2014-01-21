#ifndef PUZZLEQOBJECT_H
#define PUZZLEQOBJECT_H
#include <QLabel>
#include <memory>

namespace puzzle {
    class IntPuzzle;
}

class PuzzleQObject : public QLabel
{
    Q_OBJECT
public:
    explicit PuzzleQObject(QWidget *parent = 0);

    void setPuzzle(std::shared_ptr<puzzle::IntPuzzle> puzzle);
    const std::shared_ptr <puzzle::IntPuzzle> getPuzzle();
    int getID();


protected:
    std::shared_ptr <puzzle::IntPuzzle> puzzle;
    
};

class QLabelPuzzle : public PuzzleQObject
{
    Q_OBJECT
public:
    explicit QLabelPuzzle(QWidget *parent = 0);

};

#endif // PUZZLEQOBJECT_H

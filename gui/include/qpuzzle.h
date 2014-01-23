#ifndef QPUZZLE_H
#define QPUZZLE_H
#include <QLabel>
#include <memory>
#include "enums.h"

namespace puzzle {
    class IntPuzzle;
}
class QPuzzleBoard;

class QPuzzle : public QLabel
{
    Q_OBJECT
public:
    explicit QPuzzle(QWidget *parent = 0);

    void setInnerPuzzle(std::shared_ptr<puzzle::IntPuzzle> puzzle);
    void setParrentBoard(std::shared_ptr<QPuzzleBoard> p);
    const std::shared_ptr <puzzle::IntPuzzle> getInnerPuzzle();
    int getID();
    bool slideIfHasSpace();
    void applyPuzzleAnimation(board::SLIDE_DIRECTIONS dir);
signals:
    void clicked();

protected:
    std::shared_ptr <puzzle::IntPuzzle> puzzle;
    void mousePressEvent (__attribute__((unused)) QMouseEvent * event ) ;
    std::shared_ptr<QPuzzleBoard> parentBoard;

private slots:
    void slotClicked();

};

class QLabelPuzzle : public QPuzzle
{
    Q_OBJECT
public:
    explicit QLabelPuzzle(QWidget *parent = 0);

};

#endif // QPUZZLE_H

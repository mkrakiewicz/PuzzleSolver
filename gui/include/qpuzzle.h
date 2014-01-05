#ifndef QPUZZLE_H
#define QPUZZLE_H
#include <QLabel>
#include <memory>
#include "enums.h"

namespace puzzle {
    class IntPuzzle;
}
class QPuzzleBoard;
class QPropertyAnimation;

class QPuzzle : public QLabel
{
    Q_OBJECT
public:
    explicit QPuzzle(QWidget *parent = 0);

    void setInnerPuzzle(puzzle::IntPuzzle *puzzle);
    void setParrentBoard(QPuzzleBoard* p);
    const puzzle::IntPuzzle* getInnerPuzzle();
    int getID();
    bool slideIfHasSpace();
    void applyPuzzleAnimation(board::SLIDE_DIRECTIONS dir);

    QPropertyAnimation * createSlideAnimation(board::SLIDE_DIRECTIONS dir);

    virtual ~QPuzzle();
signals:
    void clicked();

protected:
    puzzle::IntPuzzle* puzzle;
    void mousePressEvent (__attribute__((unused)) QMouseEvent * event ) ;
    QPuzzleBoard* parentBoard;

private slots:
    void slotClicked();

};

class QLabelPuzzle : public QPuzzle
{
    Q_OBJECT
public:
    explicit QLabelPuzzle(QWidget *parent = 0);

    virtual ~QLabelPuzzle();

};

#endif // QPUZZLE_H

#ifndef QPUZZLE_H
#define QPUZZLE_H
#include <QLabel>
#include <memory>

namespace puzzle {
    class IntPuzzle;
}

class QPuzzle : public QLabel
{
    Q_OBJECT
public:
    explicit QPuzzle(QWidget *parent = 0);

    void setInnerPuzzle(std::shared_ptr<puzzle::IntPuzzle> puzzle);
    const std::shared_ptr <puzzle::IntPuzzle> getInnerPuzzle();
    int getID();

signals:
    void clicked();

protected:
    std::shared_ptr <puzzle::IntPuzzle> puzzle;
    void mousePressEvent (__attribute__((unused)) QMouseEvent * event ) ;

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

#ifndef PUZZLE_H
#define PUZZLE_H

#include <memory>

namespace puzzle {

    enum PUZZLE_TYPES
    {
        EMPTY,
        OBJECT
    };



class Puzzle
{
public:
    virtual PUZZLE_TYPES getType() = 0;
    virtual std::string toString() = 0;

    bool operator==(Puzzle &toCompare) const;
    bool operator!=(Puzzle &toCompare);

    virtual std::shared_ptr<Puzzle> clone() const = 0;
    virtual ~Puzzle();

protected:
    virtual bool isEqual(Puzzle *obj) const = 0;
};

class EmptyPuzzle : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType();
    virtual std::string toString();
    virtual std::shared_ptr<Puzzle> clone() const;
    virtual ~EmptyPuzzle();
protected:
    virtual bool isEqual(Puzzle *obj) const;

};

class PuzzleObject : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType();

    virtual ~PuzzleObject();

protected:
    virtual bool isEqual(Puzzle *obj) const;

};

class IntPuzzle : public PuzzleObject
{
public:
    const int Value;

    IntPuzzle(int value);
    virtual std::string toString();
    inline operator int()
    {
        return Value;
    }
    virtual std::shared_ptr<Puzzle> clone() const ;

    virtual ~IntPuzzle();

protected:
    virtual bool isEqual(Puzzle *obj) const;


};

}

#endif // PUZZLE_H
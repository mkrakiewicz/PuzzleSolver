#ifndef PUZZLE_H
#define PUZZLE_H

#include <memory>

enum PUZZLE_TYPES
{
    EMPTY,
    OBJECT
};

class Puzzle
{
public:
    virtual PUZZLE_TYPES getType() = 0;
    virtual void print() = 0;

    inline bool operator==(Puzzle &toCompare)
    {
        return this->isEqual(&toCompare);
    }

    inline bool operator!=(Puzzle &toCompare)
    {
        return !this->isEqual(&toCompare);
    }

    virtual std::shared_ptr<Puzzle> clone() const = 0;

    virtual ~Puzzle();

protected:
    virtual bool isEqual(Puzzle *obj) = 0;
};

class EmptyPuzzle : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType();
    virtual void print();
    virtual std::shared_ptr<Puzzle> clone() const;
    virtual ~EmptyPuzzle();
protected:
    virtual bool isEqual(Puzzle *obj);

};

class PuzzleObject : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType();

    virtual ~PuzzleObject();

protected:
    virtual bool isEqual(Puzzle *obj);

};

class IntPuzzle : public PuzzleObject
{
public:
    const int Value;

    IntPuzzle(int value);
    virtual void print();
    inline operator int()
    {
        return Value;
    }
    virtual std::shared_ptr<Puzzle> clone() const ;

    virtual ~IntPuzzle();

protected:
    virtual bool isEqual(Puzzle *obj);


};

#endif // PUZZLE_H

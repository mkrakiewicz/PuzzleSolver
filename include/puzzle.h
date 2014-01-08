#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>

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
    virtual ~Puzzle(){}
    inline bool operator==(Puzzle &toCompare)
    {
        return this->isEqual(&toCompare);
    }

    inline virtual bool operator!=(Puzzle &toCompare)
    {
        return !this->isEqual(&toCompare);
    }

protected:
    virtual bool isEqual(Puzzle *obj) = 0;
};

class EmptyPuzzle : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType()
    {
        return PUZZLE_TYPES::EMPTY;
    }

    virtual ~EmptyPuzzle(){}
    virtual void print()
    {
        std :: cout << "X";
    }

protected:
    virtual bool isEqual(Puzzle *obj)
    {
        if (obj->getType() == EMPTY)
            return true;
        return false;
    }

};

class PuzzleObject : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType()
    {
        return PUZZLE_TYPES::OBJECT;
    }

    virtual ~PuzzleObject(){}

protected:
    virtual bool isEqual(Puzzle *obj)
    {
        if (obj->getType() == OBJECT)
            return true;
        return false;
    }

};

class IntPuzzle : public PuzzleObject
{
public:
    int Value;

    IntPuzzle(const   PuzzleObject &p)    {
    }

    IntPuzzle(int value):
        Value(value)
    {
    }
    virtual void print()
    {
        std :: cout << Value;
    }
    inline operator int()
    {
        return Value;
    }

    virtual ~IntPuzzle(){}

protected:
    virtual bool isEqual(Puzzle *obj)
    {
        if (!PuzzleObject::isEqual(obj))
            return false;

        if (Value == ((IntPuzzle*)obj)->Value)
            return true;

        return false;
    }


};

#endif // PUZZLE_H

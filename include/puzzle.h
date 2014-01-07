#ifndef PUZZLE_H
#define PUZZLE_H

enum PUZZLE_TYPES
{
    EMPTY,
    OBJECT
};

class PuzzleBase
{
public:
    virtual PUZZLE_TYPES getType() = 0;
    virtual ~PuzzleBase(){}
};

class EmptyPuzzle : public PuzzleBase
{
public:
    virtual PUZZLE_TYPES getType()
    {
        return PUZZLE_TYPES::EMPTY;
    }

    virtual ~EmptyPuzzle(){}

};

class PuzzleObject : public PuzzleBase
{
public:
    virtual PUZZLE_TYPES getType()
    {
        return PUZZLE_TYPES::OBJECT;
    }

    virtual ~PuzzleObject(){}

};

class NumericPuzzle : public PuzzleObject
{
public:
    int Value;

    NumericPuzzle(int value):
        Value(value)
    {
    }

    inline operator int()
    {
        return Value;
    }

    inline bool operator==(const NumericPuzzle &toCompare) const
    {
        if (Value == toCompare.Value)
            return true;

        return false;
    }

    virtual ~NumericPuzzle(){}

};

typedef NumericPuzzle Puzzle;

#endif // PUZZLE_H

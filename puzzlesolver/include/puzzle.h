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

    bool operator==(Puzzle &toCompare);
    bool operator!=( Puzzle &toCompare);

    virtual Puzzle* clone()  = 0; // DELETE BY RECEIVER
    virtual ~Puzzle();

protected:
    virtual bool isEqual( Puzzle &obj)  = 0;
};

class EmptyPuzzle : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType();
    virtual std::string toString();
    virtual Puzzle* clone() ; // DELETE BY RECEIVER
    virtual ~EmptyPuzzle();
protected:
    virtual bool isEqual( Puzzle &obj);

};

class PuzzleObject : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType();

    virtual ~PuzzleObject();

protected:
    virtual bool isEqual( Puzzle &obj);

};

class IntPuzzle : public PuzzleObject
{
public:
     int Value;

    IntPuzzle(int value);
    virtual std::string toString();
    inline operator int()
    {
        return Value;
    }
    virtual Puzzle* clone()  ;  // DELETE BY RECEIVER

    virtual ~IntPuzzle();

protected:
    virtual bool isEqual( Puzzle &obj);


};

}

#endif // PUZZLE_H

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
    virtual PUZZLE_TYPES getType() const = 0;
    virtual std::string toString() = 0;

    bool operator==(const Puzzle &toCompare);
    bool operator!=(const Puzzle &toCompare);

    virtual std::shared_ptr<Puzzle> clone() const  = 0;
    virtual ~Puzzle();

protected:
    virtual bool isEqual(const Puzzle &toCompare)  = 0;
};

class EmptyPuzzle : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType() const;
    virtual std::string toString();
    virtual std::shared_ptr<Puzzle> clone() const ; // DELETE BY RECEIVER
    virtual ~EmptyPuzzle();
protected:
    virtual bool isEqual(const Puzzle &toCompare);

};

class PuzzleObject : public Puzzle
{
public:
    virtual PUZZLE_TYPES getType() const;

    virtual ~PuzzleObject();

protected:
    virtual bool isEqual(const Puzzle &toCompare);

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
    virtual std::shared_ptr<Puzzle> clone() const  ;  // DELETE BY RECEIVER

    virtual ~IntPuzzle();

protected:
    virtual bool isEqual( const Puzzle &toCompare);


};

}

#endif // PUZZLE_H

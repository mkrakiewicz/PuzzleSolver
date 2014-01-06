#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    Exception() throw();
    Exception(std::string message) throw();

    std::string getMessage();

    virtual ~Exception() throw();

private:
    std::string message;
};

#endif // EXCEPTIONS_H

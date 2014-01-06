#include "exceptions.h"
#include <string>

using namespace std;

Exception::Exception() throw():
    message("")
{

}

Exception::Exception(string message) throw():
    message(message)
{
}

std::string Exception::getMessage()
{
    return this->message;
}

Exception::~Exception() throw()
{
}


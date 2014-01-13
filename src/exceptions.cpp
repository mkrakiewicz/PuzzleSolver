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

std::string Exception::getMessage() const
{
    return this->message;
}

const char* Exception::what() const _GLIBCXX_USE_NOEXCEPT
{
    return getMessage().c_str();
}

Exception::~Exception() throw()
{
}


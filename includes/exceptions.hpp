#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class SocketCreationFailed : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Can't create socket properly";
    };
};

class SocketBindingFailed : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Can't bind socket properly";
    };
};

class SocketListeningFailed : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Can't listen on the binded port properly";
    };
};

class TooMuchParamsFromClient : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: User has more than 15 parameters in his command";
    };
};

class TooLongCommandFromClient : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: User has sent a command longer than 512 characters";
    };
};
#endif // !EXCEPTIONS_HPP
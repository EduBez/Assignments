#ifndef LOGGING_EXCEPTION_HPP_INCLUDED
#define LOGGING_EXCEPTION_HPP_INCLUDED

#pragma once

#include "LoggingSystem.hpp"

using namespace std;

namespace brokencode {
namespace exception {
        
class LoggingException : public std::exception {
public:
    explicit LoggingException(string &&what) : What { move(what.c_str()) } {}
    virtual ~LoggingException() = default;
    const char* what() const noexcept override final {
        return What;
    }
private:
    const char *What;
};
    
class InvalidAccessTokenException final : public LoggingException {
public:
    InvalidAccessTokenException() : LoggingException("InvalidAccessTokenException") {}
    ~InvalidAccessTokenException() {}
};

class InvalidCredentialsException final : public LoggingException {
public:
    InvalidCredentialsException() : LoggingException("InvalidCredentialsException") {}
    ~InvalidCredentialsException() {}
};
    
class RegisterApplicationException final : public LoggingException {
public:
    RegisterApplicationException() : LoggingException("RegisterApplicationException") {}
    ~RegisterApplicationException() {}
};
    
}
}

#endif //LOGGING_EXCEPTION_HPP_INCLUDED

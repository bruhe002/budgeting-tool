////////////////////////////////////////////////////////////
// @InvalidOptionException.h
//
// @author Eric Bruhns
//
////////////////////////////////////////////////////////////
#ifndef INVALIDOPTIONEXCEPTION_H_
#define INVALIDOPTIONEXCEPTION_H_

#include <exception>
#include <string>

namespace except{

class InvalidOptionException : public std::exception {
private:
    std::string msg_;

public:
    InvalidOptionException() : msg_("ERROR: Invalid Option! Please try again...") 
    {}

    InvalidOptionException(const char* msg) : msg_(msg) {}

    const char* what() const throw() {
        return msg_.c_str();
    }
};

}  // namespace except
#endif  // INVALIDOPTIONEXCEPTION_H_
#ifndef EXCEPTION_VALIDATOR_H
#define EXCEPTION_VALIDATOR_H

#include <stdexcept>
#include <string>

class exception_validator : public std::runtime_error {
    
    public:
    explicit exception_validator(const std::string& message);
};
#endif
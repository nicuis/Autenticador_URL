#ifndef ARGUMENTS_VALIDATOR_H
#define ARGUMENTS_VALIDATOR_H

#include <memory>
#include <string>

class ArgumentValidator {
    
    public:
        void validateArgs(int argc, char* argv[]) const;
};
#endif
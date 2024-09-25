#ifndef ARGUMENTS_VALIDATOR_H
#define ARGUMENTS_VALIDATOR_H

#include <memory>
#include <string>

class ArgumentValidator {
    
    public:
        static void validateArgs(int argc, char* argv[]);
};
#endif